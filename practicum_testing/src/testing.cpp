//#include "search_server.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

/* Подставьте вашу реализацию класса SearchServer сюда */

/*
 Подставьте сюда вашу реализацию макросов
 ASSERT, ASSERT_EQUAL, ASSERT_EQUAL_HINT, ASSERT_HINT и RUN_TEST
 */
void Print(ostream &out, const DocumentStatus &s) {
	if (s == DocumentStatus::ACTUAL) {
		out << "DocumentStatus::ACTUAL"s;
	} else if (s == DocumentStatus::IRRELEVANT) {
		out << "DocumentStatus::IRRELEVANT"s;
	} else if (s == DocumentStatus::BANNED) {
		out << "DocumentStatus::BANNED"s;
	} else if (s == DocumentStatus::REMOVED) {
		out << "DocumentStatus::REMOVED"s;
	}
}
ostream& operator<<(ostream &out, const DocumentStatus &v) {
	Print(out, v);
	return out;
}

template
void RunTestImpl(Func func, const string func_str) {
	func();
	cerr << func_str << " OK" << endl;
}

//#define RUN_TEST(func) RunTestImpl(func, #func)

template<typename T, typename U>
void AssertEqualImpl(const T &t, const U &u, const string &t_str,
		const string &u_str, const string &file, const string &func,
		unsigned line, const string &hint) {
	if (t != u) {
		cerr << boolalpha;
		cerr << file << "("s << line << "): "s << func << ": "s;
		cerr << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
		cerr << t << " != "s << u << "."s;
		if (!hint.empty()) {
			cerr << " Hint: "s << hint;
		}
		cerr << endl;
		abort();
	}
}

void AssertImpl(bool value, const string &expr_str, const string &file,
		const string &func, unsigned line, const string &hint) {
	if (!value) {
		cerr << file << "("s << line << "): "s << func << ": "s;
		cerr << "Assert("s << expr_str << ") failed."s;
		if (!hint.empty()) {
			cerr << " Hint: "s << hint;
		}
		cerr << endl;
		abort();
	}
}
//#define ASSERT(expr) AssertImpl(!!(expr), #expr, FILE, FUNCTION, LINE, ""s)

//#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, FILE, FUNCTION, LINE, (hint))

//#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, FILE, FUNCTION, LINE, ""s)

//#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, FILE, FUNCTION, LINE, (hint))

// -------- Начало модульных тестов поисковой системы ----------

// Тест проверяет, что поисковая система исключает стоп-слова при добавлении документов
void TestExcludeStopWordsFromAddedDocumentContent() {
	const int doc_id = 42;
	const string content = "cat in the city"s;
	const vector ratings = { 1, 2, 3 };
	{
		SearchServer server;
		server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
		const auto found_docs = server.FindTopDocuments("in"s);
		ASSERT_EQUAL(found_docs.size(), 1u);
		const Document &doc0 = found_docs[0];
		ASSERT_EQUAL(doc0.id, doc_id);
	}

	{

		SearchServer server;

		server.SetStopWords("in the"s);

		server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);

		ASSERT_HINT(server.FindTopDocuments("in"s).empty(),
				"Stop words must be excluded from documents"s);

	}

}

//Тест проверяет, что стоп-слова исключаются из текста документов
void TestStopWords() {
	SearchServer server;
	server.AddDocument(1, "cat in the city", DocumentStatus::ACTUAL,
			{ 1, 2, 3 });
	auto found_doc = server.MatchDocument("cat in the city"s, 1);
	vector words = get < 0 > (found_doc);
	ASSERT_EQUAL(words[0], "cat"s);
	ASSERT_EQUAL(words[1], "city"s);
	ASSERT_EQUAL(words[2], "in"s);
	ASSERT_EQUAL(words[3], "the"s);
	server.SetStopWords("in the"s); //добавляем стоп- слова
	found_doc = server.MatchDocument("cat in the city"s, 1);
	words = get < 0 > (found_doc);
	ASSERT_EQUAL(words.size(), 2u);
	ASSERT_EQUAL(words[0], "cat"s);
	ASSERT_EQUAL(words[1], "city"s);
}
//Тест проверяет, что документы, содержащие минус-слова из поискового запроса, не включаются в результаты поиска.
void TestMinusWords() {
	SearchServer server;
	server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL,
			{ 8, -3 });
	server.AddDocument(1, "пушистый кот пушистый хвост"s,
			DocumentStatus::ACTUAL, { 7, 2, 7 });
	server.AddDocument(2, "ухоженный пёс выразительные глаза"s,
			DocumentStatus::ACTUAL, { 5, -12, 2, 1 });
	auto found_docs = server.FindTopDocuments("ухоженный кот"s);
	ASSERT_EQUAL(found_docs.size(), 3u);
	found_docs = server.FindTopDocuments("ухоженный -кот"s);
	ASSERT_EQUAL_HINT(found_docs.size(), 1u,
			"Documents containing minus words from the search query are not included in the search"s);
}
void TestRating() {
	SearchServer server;
	server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL,
			{ 7, 2, 6 });
	auto found_docs = server.FindTopDocuments("пушистый кот"s);
	ASSERT_EQUAL(found_docs[0].rating, 5);
}
void TestCountRelevance() {
	SearchServer server;
	server.AddDocument(0, "белый кот модный ошейник"s, DocumentStatus::ACTUAL, {
			8, -3 });
	server.AddDocument(1, "пушистый хвост"s, DocumentStatus::ACTUAL,
			{ 7, 2, 7 });
	auto found_docs = server.FindTopDocuments("пушистый кот"s);
	ASSERT(abs(found_docs[0].relevance - 0.346574) < 1e-6);
	ASSERT(abs(found_docs[1].relevance - 0.1732874) < 1e-6);
}
//Тест на соответствие документов поисковому запросу. Должны быть возвращены все слова из поискового запроса, присутствующие в документе. Если есть соответствие хотя бы по одному минус-слову, возвращается пустой список слов
void TestMatchDocument() {
	const int doc_id = 42;
	const string content = "cat in the city"s;
	const vector ratings = { 1, 2, 3 };
	SearchServer server;
	server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
	const string query = "cat city";
	auto mathdo = server.MatchDocument(query, doc_id);
	vector words = get < 0 > (mathdo);
	DocumentStatus s = get < 1 > (mathdo);
	ASSERT_EQUAL(words[0], "cat");
	ASSERT_EQUAL(words[1], "city");
	ASSERT_EQUAL(s, DocumentStatus::ACTUAL);
	mathdo = server.MatchDocument("cat -in"s, doc_id);
	words = get < 0 > (mathdo);
	ASSERT(words.empty());
}
void TestAddDocument() {
	SearchServer server;
	const int doc_id = 4;
	const string text = "cat and dog in the city"s;
	const vector ratings = { 1, 2, 3 };
	ASSERT(server.FindTopDocuments("dog"s).empty());
	server.AddDocument(doc_id, text, DocumentStatus::ACTUAL, ratings);
	const auto found_docs = server.FindTopDocuments("dog in the city"s);
	ASSERT_EQUAL(found_docs.size(), 1u);
}
void TestFindTopDocuments() {
	SearchServer server;
	ASSERT(server.FindTopDocuments("cat"s).empty());
	server.AddDocument(1, "cat and dog in the city", DocumentStatus::ACTUAL, {
			1, 3, 5 });
	server.AddDocument(2, "small cat and big dogs"s, DocumentStatus::BANNED, {
			4, 2, 1 });
	server.AddDocument(0, "white cat on the street"s, DocumentStatus::ACTUAL, {
			1, 3, 5 });
	auto found_docs = server.FindTopDocuments("cat"s);
	ASSERT_EQUAL(found_docs.size(), 2u);
	DocumentStatus status = DocumentStatus::BANNED;
	found_docs = server.FindTopDocuments("cat"s, status);
	ASSERT_EQUAL(found_docs.size(), 1u);
	found_docs = server.FindTopDocuments("cat"s,
			[](int document_id, DocumentStatus status, int rating) {
				return document_id % 2 == 0;
			});
	ASSERT_EQUAL(found_docs.size(), 2u);

}
// Функция TestSearchServer является точкой входа для запуска тестов
void TestSearchServer() {
	RUN_TEST(TestExcludeStopWordsFromAddedDocumentContent);
	RUN_TEST(TestStopWords);
	RUN_TEST(TestMinusWords);
	RUN_TEST(TestRating);
	RUN_TEST(TestCountRelevance);
	RUN_TEST(TestMatchDocument);
	RUN_TEST(TestAddDocument);
}

// --------- Окончание модульных тестов поисковой системы -----------

int main() {
	TestSearchServer();
// Если вы видите эту строку, значит все тесты прошли успешно
	cout << "Search server testing finished"s << endl;
}
