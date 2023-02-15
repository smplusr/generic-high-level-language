#include "lang.h"




void coreDefine (lang_t *lang) {
	char *word = lang->string->getWord (lang->string, WORD_END);
/*	char *word = (char *) lang->update (lang);	*/
	size_t value = lang->update (lang);
	lang->dict->set(lang->dict, word, value, data);
}



#ifdef LANG_EXTRA
/* DEPRECATED
 * Use string concatenation and dynamic replacement instead
 * ie:	define a 42
 * 	define b string " a "
 * 	put b				doesn't work, puts 'a'
 * 	
 * 	define c string " put "
 * 	eval conc c b			puts 42
 * */

size_t coreValue (lang_t *lang) {
	pair_t *pair = lang->dict->get (lang->dict, (char *) lang->update (lang));
	return (pair)
		? pair->value.data
		: (size_t) NULL;
}
#endif



void coreEval (lang_t *lang) { lang->string->stream->set (lang->string->stream, (char *) lang->update (lang)); }

size_t coreNot (lang_t *lang) { return (size_t) !lang->update (lang); }

void coreCond (lang_t *lang) {
	((bool) lang->update (lang))
		? (void) lang->update (lang)
		: (void) lang->string->getWord (lang->string, WORD_END);	/* Needs a word ignore function? */
}

char *coreInput (lang_t *lang) {
	char *ptr = lang->string->stream->get (lang->string->stream),
	     *str;

	lang->string->stream->set (lang->string->stream, "");
	str = lang->string->getWord (lang->string, "\n");
	lang->string->stream->set (lang->string->stream, ptr);

	return str;
}

void coreDelete (lang_t *lang) { 	
	char *word = lang->string->getWord (lang->string, WORD_END);
	pair_t *pair = lang->dict->get (lang->dict, word);

	lang->dict->remove (lang->dict, word);
	lang->string->remove (lang->string, word);

	if (pair) lang->string->remove (lang->string, (char *) pair->value.data);
}
