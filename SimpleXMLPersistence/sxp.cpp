#include "sxp.h"

namespace SXP {
//	std::string TagHashtable::table[HTSIZE];
	TagHashtable *g_pHashTable = 0;

	// add the tag to the table right on construction
	Tag::Tag(const char *name) 
	{
		ch = name;
		dw = ~0;
		TagHashtable::TagHT().Add(*this);
	}

	void CFileOutStream::WriteSubElement(IPersistObj *pObj, dict& attribs) {
		pObj->WriteElement(this, attribs);
	}

	const char *IElement::Name() { return 0; }
	const char *IElement::Attrib(const char *attrName) { return 0; }

	int IElement::IsA(const char *name) { return 0; }
	int IElement::IsA(Tag& t) { return 0; }
	int IElement::AttribIs(const char *attrName, const char *val) { return 0; }

	ErrCode RemapError(int expat_err) 
	{
		switch( expat_err ) {
		case XML_ERROR_NONE :                          return err_no_error;
		case XML_ERROR_NO_MEMORY :                     return err_no_memory;
		case XML_ERROR_SYNTAX :                        return err_syntax;
		case XML_ERROR_NO_ELEMENTS :                   return err_no_elements;
		case XML_ERROR_INVALID_TOKEN :                 return err_invalid_token;
		case XML_ERROR_UNCLOSED_TOKEN :                return err_unclosed_token;
		case XML_ERROR_PARTIAL_CHAR :                  return err_partial_char;
		case XML_ERROR_TAG_MISMATCH :                  return err_tag_mismatch;
		case XML_ERROR_DUPLICATE_ATTRIBUTE :           return err_duplicate_attribute;
		case XML_ERROR_JUNK_AFTER_DOC_ELEMENT :        return err_junk_after_doc_element;
		case XML_ERROR_PARAM_ENTITY_REF :              return err_param_entity_ref;
		case XML_ERROR_UNDEFINED_ENTITY :              return err_undefined_entity;
		case XML_ERROR_RECURSIVE_ENTITY_REF :          return err_recursive_entity_ref;
		case XML_ERROR_ASYNC_ENTITY :                  return err_async_entity;
		case XML_ERROR_BAD_CHAR_REF :                  return err_bad_char_ref;
		case XML_ERROR_BINARY_ENTITY_REF :             return err_binary_entity_ref;
		case XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF : return err_attribute_external_entity_ref;
		case XML_ERROR_MISPLACED_XML_PI :              return err_misplaced_xml_pi;
		case XML_ERROR_UNKNOWN_ENCODING :              return err_unknown_encoding;
		case XML_ERROR_INCORRECT_ENCODING :            return err_incorrect_encoding;
		case XML_ERROR_UNCLOSED_CDATA_SECTION :        return err_unclosed_cdata_section;
		case XML_ERROR_EXTERNAL_ENTITY_HANDLING :      return err_external_entity_handling;
		case XML_ERROR_NOT_STANDALONE :                return err_not_standalone;
		default :                                      return err_unknown;
		}
	}

	IData::~IData() {}

	// escape a char string - remove &<>" and replace with escape codes
	string XMLEscape(const char *pstr) 
	{
		const char *p;
		string ret;
		for(p = pstr; *p; p++) {
			switch( *p ) {
			case '&': ret.append("&amp;",  5); break;
			case '<': ret.append("&lt;",   4); break;
			case '>': ret.append("&gt;",   4); break;
			case '"': ret.append("&quot;", 6); break;
			default:  ret.append(1, *p);
			}
		}
		return ret;
	}

	// escape a wide character char string - remove &<>" and replace with escape codes, convert UCS-16 to UTF-8
	string XMLEscapeW(const wchar_t *pstr) 
	{
		const wchar_t *p;
		string ret;
		for(p = pstr; *p; p++) {
			if( *p < 0x80 ) {
				switch( *p ) {
				case L'&': ret.append("&amp;"); break;
				case L'"': ret.append("&quot;"); break;
				case L'<': ret.append("&lt;"); break;
				case L'>': ret.append("&gt;"); break;
				default:   ret.append(1, (char)*p);
				}
			} else {
				if( *p < 0x800 ) {
					ret.append(1, (0xC0 | ((*p) >> 6) ));
					ret.append(1, (0x80 | ((*p) & 0x3F )));
				} else {
					ret.append(1, (0xE0 | ( (*p) >> 12)         ));
					ret.append(1, (0x80 | (((*p) >>  6) & 0x3F )));
					ret.append(1, (0x80 | ( (*p)        & 0x3F )));
				}
			}
		}
		return ret;
	}

	string XMLUnEscape(const char *pstr) {
		const char *p;
		string ret;
		for(p = pstr; *p; p++) {
			if( *p != '&' ) {
				ret.append(1, *p);
			} else {
				if( strcmp(p+1, "amp;") == 0 ) {
					p += 4;
					ret.append(1, '&');
				} else if( strcmp(p+1, "lt;") == 0 ) {
					p += 3;
					ret.append(1, '<');
				} else if( strcmp(p+1, "gt;") == 0 ) {
					p += 3;
					ret.append(1, '>');
				} else if( strcmp(p+1, "quot;") == 0 ) {
					p += 5;
					ret.append(1, '"');
				}
			}
		}
		return ret;
	}

	// remove XML escapes (&amp; etc), convert UTF-8 to UCS-16
	wstring XMLUnEscapeW(const char *pstr) {
		std::wstring ret;
		unsigned len = strlen(pstr);
		wchar_t wch;
		for(unsigned pos = 0; pos<len; pos++) {
			unsigned char c0, c1, c2;
			c0 = pstr[pos];
			if( c0 == '&' ) {
				if( strncmp(pstr+pos+1, "amp;", 4) == 0) {
					ret.append(1, L'&');
				} else if( strncmp(pstr+pos+1, "lt;", 3) == 0 ) {
					ret.append(1, L'<');
				} else if( strncmp(pstr+pos+1, "gt;", 3) == 0 ) {
					ret.append(1, L'>');
				} else if( strncmp(pstr+pos+1, "quot;", 5) == 0 ) {
					ret.append(1, L'"');
				} else {
					ret.append(1, L'&');
				}
			} else {
				if( c0 < 0x80 ) {
					ret.append(1, wchar_t(pstr[pos]));
				} else {
					c1 = pstr[pos+1];
					if( (c0 & 0xE0) == 0xC0 ) {
						wch = (c0 & 0x1F);
						wch <<= 6;
						wch |= (c1 & 0x3F);
						ret.append(1, wch);
						pos++;
					} else {
						c2 = pstr[pos+2];
						wch = (c0 & 0xF);
						wch <<= 6;
						wch |= (c1 & 0x3F);
						wch <<= 6;
						wch |= (c2 & 0x3F);
						ret.append(1, wch);
						pos++; pos++;
					}
				}
			}
		}
		return ret;
	}

	// the mighty parser itself
	CParser::CParser(IPersistObj *pRoot) {
		m_parser = XML_ParserCreate(0);
//		XML_SetUnknownEncodingHandler(m_parser, CParser::UEHandler, 0);
		XML_SetUserData(m_parser, (void *)this);
		XML_SetElementHandler(m_parser, CParser::StaticStartElement, CParser::StaticEndElement);
		XML_SetCharacterDataHandler(m_parser, CParser::StaticCharData);
		ReadTo(pRoot);
		m_bShuttingDown = 0;
	}

	// give the parser food for thought
	ErrCode CParser::Feed(const char *pData, int nLen, int bFinal) {
		if( m_parser ) {
			int i;
			if( i = XML_Parse(m_parser, pData, nLen, bFinal) ) {
				return err_no_error;
			} else {
				XML_Error e  = XML_GetErrorCode(m_parser);
				m_nErrorLine = XML_GetCurrentLineNumber(m_parser);
				m_nErrorCol  = XML_GetCurrentColumnNumber(m_parser);
				m_strError   = XML_ErrorString(e);
				return RemapError(e);
			}
		} else {
			return err_no_error;
		}
	}

	// give the parser a food for thought the lazy way
	ErrCode CParser::FeedFile(char *pchFilename) {
		char buf[8192];
		FILE *fp;
		int done;
		ErrCode err = err_no_error;
		m_strError = "No error";
		m_nErrorLine = -1;
		m_nErrorCol = -1;

		fopen_s(&fp, (const char *)pchFilename, "rt");
		if( NULL == fp) {
			// free already created parser
			XML_ParserFree(m_parser);
			m_parser = 0;

			m_strError = "Can\'t open file";
			m_nErrorLine = -1;
			m_nErrorCol = -1;
			return err_cant_open_file;
		}


		do {
			size_t len = fread(buf, 1, sizeof(buf), fp);
			done = len < sizeof(buf);
			err = Feed(buf, len, done);
			done = done || m_bShuttingDown || !m_parser || (err != err_no_error);
		} while (!done);

		fclose(fp);

		// free the parsers and the stacks
		DoShutdown();
		
		return err;
	}

	// these need to be static so they can be registered as callbacks
	// with expat
	
	void CParser::StaticStartElement(void *puserData, const XML_Char *name, const XML_Char **atts) {
		CParser *pThis = (CParser *)puserData;
		if( !pThis->m_bShuttingDown ) {
			pThis->StartElement(name, atts);
		}
	}
	void CParser::StaticEndElement(void *puserData, const XML_Char *name) {
		CParser *pThis = (CParser *)puserData;
		if( !pThis->m_bShuttingDown ) {
			pThis->EndElement(name);
		}
	}
	void CParser::StaticCharData(void *puserData, const XML_Char *data, int len) {
		CParser *pThis = (CParser *)puserData;
		if( !pThis->m_bShuttingDown ) {
			pThis->CharData(data, len);
		}
	}

	int CParser::UEHandler(void *pData, const char *pchName, XML_Encoding *info)	{
		if( strcmp(pchName, "sxp_encoding") == 0) {
			for(int i=0; i<256; i++) {
				info->map[i] = i;
			}
			info->convert = 0;
			info->release = 0;
			return 1;
		} else {
			return 0;
		}
	}

	// closing tag for the root object element encountered, stop parsing
	// DoShutdown cannot be called inside a handler call initiated by
	// expat, so actual shutdown is deferred until the next iteration of
	// the feed loop; however, events are NOT received

	void CParser::DoShutdown() {
		XML_ParserFree(m_parser);
		while( !m_EHStack.empty() ) {
			//delete m_EHStack.top(); 
			m_EHStack.pop();
		}
		while( !m_EStack.empty() ) {
			delete m_EStack.top();
			m_EStack.pop();
		}
		m_parser = 0;
	}
};

