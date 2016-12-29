#pragma once
#include "stdafx.h"
#include "kmpsearch_intf.h"
#include "kmplps_intf.h"
#include "chunkwrapper_intf.h"

using namespace std;

/* This class implements IKmpInterface
*/
class CKmpSearch : public IKmpSearch 
{
public:
	// constructor
	// \params[in] pattern Pattern to be searched in file
	// \params[in] lps longest proper prefix which is also suffix (used by KMP - preprocessed from pattern)
	// \params[in] buffer buffer from the file (based on file chunks)
	explicit CKmpSearch(const string & pattern, const TKmpLps & lps, const shared_ptr<IChunkWrapper> & spBuffer);

public:
	// \copydoc IKmpSearch::Run
	TSearchResults Run() override;

protected:
	// fill sufix in result
	// \param[in] patternBufBegin Position of the first character of searched pattern in buffer.
	string GetPrefix(long patternBufBegin);

	// fill sufix in result
	// \param[in] patternBufEnd Position of the last character of searched pattern in buffer.
	string GetSufix(long patternBufEnd);

	// detects special characters (\t or \n)
	// \param[in] ch character to be replaced
	// \return true if ch is special character; otherwise return false
	bool IsSpecialCharacter(char ch);

	// transform special characters (\t -> "\\t"; \n -> "\n")
	// \param[in] ch character to be replaced
	// \return string representation of the special character
	string TransformSpecialCharacter(char ch);

protected:
	const TKmpLps & m_lps;                       // preprocessed LPS
	const string & m_pattern;                    // pattern to be searched
	const shared_ptr<IChunkWrapper> m_spBuffer;  // buffer

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CKmpSearch object
		\param[out] spKmpSearch instance of CKmpSearch
		\params[in] pattern Pattern to be searched in file
		\params[in] lps longest proper prefix which is also suffix (used by KMP - preprocessed from pattern)
		\params[in] buffer buffer from the file (based on file chunks)
		*/
		virtual void CreateKmpSearch(shared_ptr<IKmpSearch> & spKmpSearch,
			const string & pattern,
			const TKmpLps & lps,
			const shared_ptr<IChunkWrapper> & spBuffer);
	};
};