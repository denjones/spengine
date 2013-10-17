// this file is included by sxp.h
// here "cleanly" separated is the functionality for converting
// between char * data and simple data types
// adding methods to these two interfaces automagically adds them respectively
// to the IElement and IOutStream interfaces passed to your user classes


// IDataOutput: bundles together methods for printing out simple data
// to a tag, e.g. <height>188</height> to the
// stdio.h file pointer returned by the FP() method, aided by an Indent()
// method which knows how many tabs to print before your tag.

template<class T>
interface IDataOutput :
IFilePointer<T> {
	// add more simple type writers here

	inline void WriteElement(Tag& t, int val) {
		Indent();
		fprintf(FP(), "<%s>%d</%s>\n", t.ch, val, t.ch);
	}

	inline void WriteElement(Tag& t, double val) {
		Indent();
		fprintf(FP(), "<%s>%g</%s>\n", t.ch, val, t.ch);
	}

	inline void WriteElement(Tag& t, string val) {
		Indent();
		if( !val.empty() )
			fprintf(FP(), "<%s>%s</%s>\n", t.ch, XMLEscape(val.c_str()).c_str(), t.ch);
		else
			fprintf(FP(), "<%s/>\n", t.ch);
	}

	inline void WriteElement(Tag& t, wstring val) {
		Indent();
		if( !val.empty() )
			fprintf(FP(), "<%s>%s</%s>\n", t.ch, XMLEscapeW(val.c_str()).c_str(), t.ch);
		else
			fprintf(FP(), "<%s/>\n", t.ch);
	}

	inline void WriteElement(Tag& t, float val) {
		Indent();
		fprintf(FP(), "<%s>%g</%s>\n", t.ch, val, t.ch);
	}

	inline void WriteElement(Tag& t, bool val) {
		Indent();
		fprintf(FP(), "<%s>%s</%s>\n", t.ch, val ? "true" : "false", t.ch);
	}
	
};

// IDataInput: bundles together methods for converting from the char*
// returned by the Data() method (inherited from IData).

interface IDataInput: public IData
{
	inline void Retrieve(int& val) {
		val = atol(Data());
	}

	inline void Retrieve(double& val) {
		val = atof(Data());
	}

	inline void Retrieve(string& val) {
		val = XMLUnEscape(Data());
	}

	inline void Retrieve(wstring& val) {
		val = XMLUnEscapeW(Data());
	}

	inline void Retrieve(float& val) {
		val = (float)atof(Data());
	}
	
	inline void Retrieve(bool& val) {
		string s = Data();
		val = ( s == "true" );
	}
};

