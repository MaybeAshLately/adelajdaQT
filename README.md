# Adelajda QT version


## Introduction

Adelajda is app designed for flashcard learning. It was designed using C++ version 17.

Adelajda allows user to create multiple lists, where each item contains a pair of words in two languages, and optionally a comment and background color information for the item.
Both the list information (name and languages names) and the list item content can be edited. A list or an item can also be deleted.


### Learning Modes
Adelajda offers two learning modes:
- Mode A - The app displays a word in one language, and after user clicks the "reveal" button, its translation is shown.
The user can chose whether to display, at the beginning the word from the first, second, or both languages.

- Mode B - The app displays a word in one language, user can enter its translation into EditText box, and check if it is correct.
As in mode A the user can chose whether to display, at the beginning the word from the first, second, or both languages.
Additionally, the user can decide whether, after misspelling a word, it should be skipped, repeated immediately, or repeated before the end of list.


## About project
This repository contains Windows version of app. In repository named "Adelajda" there is a mobile (android) version. Logic of both versions is almost identical (apart from language differences).
In windows the GUI was created using the QT framework (https://www.qt.io/), version 6.7.2 under the GPL license.

### License

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <https://www.gnu.org/licenses/>.
 
