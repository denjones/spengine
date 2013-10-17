#if !defined(__SXP__H)
#define __SXP__H

// expat
#include "expat.h"

#if defined(_MSC_VER)
	// link expat lib too
#pragma warning(disable: 4786)
#   pragma comment(lib, "expat.lib")

#endif

// STL
#pragma warning( disable: 4786 ) // damn identifier truncated's
#include <stack>
#include <string>
#include <list>
#include <map>

// atol, ltoa etc.
#include <stdlib.h>

// fopen, fread, fprintf
#include <stdio.h>

// strcmp :-/
#include <string.h>

// errrr.... I've had too much COM lately...
#ifndef interface
#define interface struct
#endif 

namespace SXP {

	// ERRORS

	enum ErrCode {
		err_no_error,
		err_cant_open_file,
		err_no_memory,
		err_syntax,
		err_no_elements,
		err_invalid_token,
		err_unclosed_token,
		err_partial_char,
		err_tag_mismatch,
		err_duplicate_attribute,
		err_junk_after_doc_element,
		err_param_entity_ref,
		err_undefined_entity,
		err_recursive_entity_ref,
		err_async_entity,
		err_bad_char_ref,
		err_binary_entity_ref,
		err_attribute_external_entity_ref,
		err_misplaced_xml_pi,
		err_unknown_encoding,
		err_incorrect_encoding,
		err_unclosed_cdata_section,
		err_external_entity_handling,
		err_not_standalone,	
		err_unknown
	};

	ErrCode RemapError(int expat_err);
	
	// a few shortcuts
	typedef std::string string; // we deserve a string of our own!
	typedef std::wstring wstring; // and a wchar_t variation
	typedef std::map<string, string> dict; // for the attribs

	// Interface forwards

	interface IPersistObj;
	struct Tag;

	template<class T>
	interface IFilePointer {
		inline FILE *FP() { return ((T *)this)->FP(); }
		inline void Indent()   { ((T *)this)->Indent(); }
	};

	interface IData {
		virtual ~IData();
		virtual const char *Data() = 0;
	};

	// helper functions

	// escape a char string - remove &<>" and replace with escape codes
	string XMLEscape(const char *pstr);

	// escape a wide character char string - remove &<>" and replace with escape codes, convert UCS-16 to UTF-8
	string XMLEscapeW(const wchar_t *pstr);

	// remove XML escapes (&amp; etc)
	string XMLUnEscape(const char *pstr);

	// remove XML escapes (&amp; etc), convert UTF-8 to UCS-16
	inline wstring XMLUnEscapeW(const char *pstr);

#include "sxp_data.h"

	// abstraction for the output stream - something which knows
	// how to begin the XML document, how to write object begin/end tags
	// and simple data elements
	template<class T>
	interface IOutStreamT: 
	public IDataOutput<T> {
		inline void BeginXML(void) { ((T *)this)->BeginXML(); }

		inline void BeginObject(Tag& t, dict& attribs) { ((T *)this)->BeginObject(t, attribs); }
		inline void EndObject  (Tag& t) { ((T *)this)->EndObject(t); }

		// recursively write other objects
		inline void WriteSubElement(IPersistObj *pObj, dict& attribs) { 
			((T *)this)->WriteSubElement(pObj, attribs); 
		} 
	};

	// abstraction for an XML element, with extractor methods
	// for the name of the element, for the "character data"
	// (the free-floating characters between the opening and closing tags),
	// and a method to access the attribs by name
	// for want of a better place (and to simplify code in the user classes),
	// the methods to read from simple data elements (like <height>187.4</height>)
	// are stuffed here

	interface IElement : public IDataInput {
		virtual ~IElement() {}
		virtual const char *Name();
		virtual const char *Attrib(const char *attrName);

		virtual int IsA(const char *name);
		virtual int IsA(Tag& t);
		virtual int AttribIs(const char *attrName, const char *val);
	};

	// The user classes need only this much access to the parser:
	// a way to redirect parsing events into child element handlers
	// and a way to stop it on error or when it doesn't need more data
	interface IParser {
		virtual void ReadTo( IPersistObj *pTarget ) = 0;
		virtual void Shutdown( void ) = 0;
	};

	// Implementation follows. Please stop reading here :-)

	// the hashtable facility, used for element names

	// wraps the element names ("tags") in a dual string-hash key
	// representation
	struct Tag {
		const char *ch;
		unsigned long dw;
		Tag(const char *name);
		Tag(){}
	};

// hashtable size
// this should be at least 3-4 times the number of tags you use
// the more, the better
#define HASHTABLESIZE		256

	// a singleton hashtable
	// for tags

	class TagHashtable;
	extern TagHashtable *g_pHashTable;

	class TagHashtable {
	private:
		TagHashtable() { }
	public:
		~TagHashtable(){}

		inline static TagHashtable& TagHT() {
			if( g_pHashTable ) {
				return *g_pHashTable;
			} else {
				g_pHashTable = new TagHashtable;
				return *g_pHashTable;
			}
		}

		string table[HASHTABLESIZE]; // if you have lots of tags, increase this

		// the basic hash function
		inline unsigned long Hash(const char *ch) {
			unsigned long dw = 0;
			for (; *ch; dw = (dw << 5) - dw + *ch++);
			return dw;
		}

		// add a tag's char* member to the hashtable and
		// fill the dword member;
		// plain vanilla hash, lookup, strcmp, linear search
		inline unsigned long Add(Tag& t) {
			unsigned int dw = Hash(t.ch) % HASHTABLESIZE;
			while(1) {
				if( table[dw].empty() ) {
					table[dw] = t.ch;
					return t.dw = dw;
				} else if( table[dw].compare( t.ch ) == 0 ) {
					return t.dw = dw;
				} else {
					dw++; 
					dw %= HASHTABLESIZE;
				}
			}
		}

		// find the hash value of a string which shouldn't be added to the
		// table; return ~0 on "not found"
		inline unsigned long Lookup(const char *ch) {
			unsigned int dw = TagHashtable::TagHT().Hash(ch) % HASHTABLESIZE;
			while(1) {
				if( table[dw].empty() ) {
					return ~0;
				} else if( table[dw].compare( ch ) == 0 ) {
					return dw;
				} else {
					dw++; 
					dw %= HASHTABLESIZE;
				}
			}
		}
	};

	static void DestroyHT()
	{
		if (g_pHashTable)
		{
			delete g_pHashTable;
			g_pHashTable = NULL;
		}
	}

	// IOutStream to an stdio file.
	class CFileOutStream : 
	public IOutStreamT<CFileOutStream> {
	public:
		FILE *m_fp;
	private:
		int m_nIndent;

		// ugly...
	public:
		inline FILE *FP() {
			return m_fp;
		}

		inline void Indent() {
			for(int i=0; i<m_nIndent; i++)
				fputc('\t', m_fp);
		}

		inline CFileOutStream(const char *chFilename) {
			m_fp = NULL;
			fopen_s(&m_fp, chFilename, "wt");
			m_nIndent = 0;
		}

		inline CFileOutStream(FILE *fp) {
			m_fp = fp;
			m_nIndent = 0;
		}

		~CFileOutStream() {
			fclose(m_fp);	
		}
		
		inline void BeginXML(void) {
			// UTF-8 encoding is used because it allows relatively painless
			// support for storing widechars as character data, via
			// conversion functions in IElement::Retrieve() and 
			// IOutStream::WriteElement
			fprintf(m_fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		}

		inline void BeginObject(Tag& t, dict& attribs) {
			Indent(); m_nIndent++;
			fprintf(m_fp, "<%s", t.ch);
			for(dict::iterator i=attribs.begin(); i!=attribs.end(); i++) {
				fprintf(m_fp, " %s=\"%s\"",
					(*i).first.c_str(),
					(*i).second.c_str() );
			}
			fprintf(m_fp, ">\n");
		}

		inline void EndObject  (Tag& t) {
			m_nIndent--;
			Indent();
			fprintf(m_fp, "</%s>\n", t.ch);
		}

		void WriteSubElement(IPersistObj *pObj, dict& attribs); 
	};

	typedef IOutStreamT<CFileOutStream> IOutStream;

	// IElement implemented with STL strings

	class CElement : public IElement {
		string m_strName;
		string m_strData;
		dict m_Attribs;
		unsigned long m_dwTagHash;

	public:
		CElement() {}
		~CElement() { 
			m_strData.erase(); 
		}
		
		inline void Init(const XML_Char *pchName, const char **ppchAttrib) {
			m_dwTagHash = ~0;
			m_strName = pchName;
			m_strData.erase();
			m_Attribs.clear();

			for(const char **pp = ppchAttrib; *pp != 0; pp += 2) {
				m_Attribs[ string(pp[0]) ] =
					string( pp[1] );
			}
		}

		inline void AddData(const char *pchData, int len) {
			m_strData.append(pchData, len);
		}

		// IData
		inline const char *Data() {
			return m_strData.c_str();
		}

		// IElementT
		inline const char *Name() {
			return m_strName.c_str();
		}
		inline const char *Attrib(const char *attrName) {
			return (m_Attribs[ string(attrName) ]).c_str();
		}
		inline int AttribIs(const char *attrName, const char *val) {
			return ((m_Attribs[ string(attrName) ]).compare(val) == 0);
		}
		inline int IsA(Tag& t) {
			if( m_dwTagHash == ~0 ) {
				m_dwTagHash = TagHashtable::TagHT().Lookup(m_strName.c_str());
			}
			return( t.dw == m_dwTagHash );
		}
		inline int IsA(const char *pchName) {
			return( !m_strName.compare(pchName) );
		}
	};

	// IPersistObj is implemented by the user classes;
	// it contains both reading and writing functionality
	interface IPersistObj {
		// this should return the identifier used for the elements
		// describing objects of the user class; this should be a
		// function used also by the IPersistObj::WriteElement implementation
		virtual Tag GetClassTag() = 0;

		// the user class should write itself out, using the IOutStream
		// members for its "simple" members and calling WriteElement
		// recursively for any contained objects
		// some of its attributes might be supplied from its container
		// (which is supposed to call WriteElement in the first place)
		virtual void  WriteElement(IOutStream *pOut, dict& attribs) = 0;

		// this is called for each element within the "this" element,
		// for which the "this" element is immediate parent
		// it is called when the open element tag is encountered,
		// and only the Name() and Attrib() of pElement values are valid
		virtual void BeginElement(IParser *pIn, IElement *pElement) = 0;

		// this is called when the corresponding close element
		// tag is encountered, and the Data() member of pElement is
		// also valid
		// NOTE: each object receives both its own BeginElement so it can
		// process its own element tag attributes, and its own EndElement
		// so it can process its own character data
		virtual void EndElement(IParser *pIn, IElement *pElement) = 0;
	};

	// the mighty parser itself
	class CParser : public IParser {
		std::stack<IPersistObj *> m_EHStack; // event handlers
		std::stack<CElement *> m_EStack; // elements
		XML_Parser m_parser;

		int m_bShuttingDown;
		int m_nErrorLine, m_nErrorCol; // position of error as reported by expat
		std::string m_strError;

	public:
		// The parser begins feeding element events into a "root" object -
		// typically an object factory of sorts
		CParser(IPersistObj *pRoot);

		int GetErrorLine() { return m_nErrorLine; }
		int GetErrorCol()  { return m_nErrorCol; }
		std::string GetErrorStr() { return m_strError; }
		void GetErrorPos(int& line, int& col) {
			line = m_nErrorLine;
			col  = m_nErrorCol;
		}

		// give the parser food for thought
		inline ErrCode Feed(const char *pData, int nLen, int bFinal = 1);

		// give the parser a food for thought the lazy way
		ErrCode FeedFile(char *pchFilename);

		// IParser::ReadTo -> redirect event stream into a new IPersistObj
		inline void ReadTo( IPersistObj *pPI ) {
			m_EHStack.push(pPI);
		}

		// these need to be static so they can be registered as callbacks
		// with expat
		
		static void StaticStartElement(void *puserData, const XML_Char *name, const XML_Char **atts);
		static void StaticEndElement(void *puserData, const XML_Char *name);
		static void StaticCharData(void *puserData, const XML_Char *data, int len);
		static int UEHandler(void *pData, const char *pchName, XML_Encoding *info);

		// closing tag for the root object element encountered, stop parsing
		// DoShutdown cannot be called inside a handler call initiated by
		// expat, so actual shutdown is deferred until the next iteration of
		// the feed loop; however, events are NOT received
		inline void Shutdown() {
			m_bShuttingDown = 1;
		}

		void DoShutdown();

	private:
		// opening element tag encountered; push on element stack
		// and send to current handler
		inline void StartElement(const XML_Char *name, const char **atts) {
			CElement *pElement = new CElement;
			pElement->Init(name, atts);
			m_EStack.push(pElement);
			m_EHStack.top()->BeginElement(this, pElement);
		}

		// closing element tag encountered;
		//   if this is the closing tag for the current event handler,
		//   pop it off the handler stack; if this empties the stack,
		//   shut down parser
		// else - just feed the element with the already completed
		// data section to the current handler, then pop it off the element
		// stack
		inline void EndElement(const XML_Char *name) {
			unsigned long dwHash = TagHashtable::TagHT().Lookup(name);
			IElement *pElement = m_EStack.top();
			m_EStack.pop();
			m_EHStack.top()->EndElement(this, pElement);
			if( dwHash == m_EHStack.top()->GetClassTag().dw ) {
				m_EHStack.pop();
				if( m_EHStack.empty() ) {
					Shutdown();
					delete pElement;
					return;
				}
			}
			delete pElement;
		}

		// add it to the current element data
		inline void CharData(const XML_Char *data, int len) {
			m_EStack.top()->AddData(data, len);
		}
	};

}

#endif // __SXP__H

