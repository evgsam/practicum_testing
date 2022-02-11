#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <list>

using namespace std;

class Editor {
public:
	Editor() = default;
	//Editor();
	// сдвинуть курсор влево
	void Left() {
		if (it_ != text_.begin()) {
			--*it_;
		}
	}

	// сдвинуть курсор вправо
	void Right() {
		if (it_ != text_.end()) {
			++*it_;
		}
	}
	// вставить символ token
	void Insert(char token) {
		text_.insert(it_, token);
	}

	// вырезать не более tokens символов, начиная с текущей позиции курсора
	void Cut(size_t tokens = 1) {
		std::list<char>::iterator end_it_1 = std::next(it_, tokens);
		if (tokens>static_cast<size_t>(distance(it_, end_it_1))){
			tokens=static_cast<size_t>(distance(it_, end_it_1));
		}

		std::list<char>::iterator end_it_ = std::next(it_, tokens);
		buffer_.insert(buffer_.begin(), it_, end_it_);
		text_.erase(it_, end_it_);
	}

	// cкопировать не более tokens символов, начиная с текущей позиции курсора
	void Copy(size_t tokens = 1) {
		if (tokens>static_cast<size_t>(distance(it_, text_.end()))){
			tokens=static_cast<size_t>(distance(it_, text_.end()));
		}
		std::list<char>::iterator end_it_ = std::next(it_, tokens);
		buffer_.insert(buffer_.begin(), it_, end_it_);
	}
	// вставить содержимое буфера в текущую позицию курсора
	void Paste() {
		text_.insert(it_, buffer_.begin(), buffer_.end());
	}

	// получить текущее содержимое текстового редактора
	std::string GetText() const {
		return {text_.begin(),text_.end()};
	}

	std::string GetBufText() const {
		return {buffer_.begin(),buffer_.end()};
	}
private:
	std::list<char> text_ { };
	std::list<char> buffer_ { };
	std::list<char>::iterator it_ = text_.begin();
};

int main() {
	Editor editor;
	const string text = "hello, world"s;
	for (char c : text) {
		editor.Insert(c);
	}
	// Текущее состояние редактора: `hello, world|`
	for (size_t i = 0; i < text.size(); ++i) {
		editor.Left();
	}
	// Текущее состояние редактора: `|hello, world`
	editor.Cut(7);
	// Текущее состояние редактора: `|world`
	// в буфере обмена находится текст `hello, `
	for (size_t i = 0; i < 5; ++i) {
		editor.Right();
	}
	// Текущее состояние редактора: `world|`
	editor.Insert(',');
	editor.Insert(' ');
	// Текущее состояние редактора: `world, |`
	editor.Paste();
	// Текущее состояние редактора: `world, hello, |`
	editor.Left();
	editor.Left();
	//Текущее состояние редактора: `world, hello|, `
	editor.Cut(3);  // Будут вырезаны 2 символа
	// Текущее состояние редактора: `world, hello|`
	cout << editor.GetText();
	return 0;

}
