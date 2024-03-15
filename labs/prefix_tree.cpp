#include <iostream>
#include <vector>
#include <queue>
#include <map>

struct Trie {
    std::map<char, Trie*> to;
    bool isEndOfWord;
    Trie* link;
    char key;
    std::string value;

    Trie() : isEndOfWord(false), link(nullptr), key(' '), value("") {}
};

void buildSuffixLinks(Trie* root) {
    std::queue<Trie*> q;
    q.push(root);

    while (!q.empty()) {
        Trie* curr = q.front();
        q.pop();

        for (const auto& it : curr->to) {
            char symbol = it.first;
            Trie* child = it.second;
            q.push(child);

            Trie* link = curr->link;
            while (link && link->to.find(symbol) == link->to.end()) {
                link = link->link;
            }
            if (link) {
                child->link = link->to[symbol];
            }
            else {
                child->link = root;
            }
        }
    }
}

void printSuffixLinks(Trie* root) {
    std::cout << "Node\tSuffix Link\n";
    std::queue<Trie*> queue;
    queue.push(root);

    while (!queue.empty()) {
        Trie* current = queue.front();
        queue.pop();

        std::cout << current->value << "\t";
        if (current != root && current->link != nullptr) {
            std::cout << current->link->value;
        }
        std::cout << "\n";

        for (auto& pair : current->to) {
            queue.push(pair.second);
        }
    }
}

void insertWord(Trie* root, const std::string& word) {
    Trie* current = root;
    for (char letter : word) {
        if (current->to.find(letter) == current->to.end()) {
            current->to[letter] = new Trie();
            current->to[letter]->key = letter;
            current->to[letter]->value = current->value + letter;
        }
        current = current->to[letter];
    }
    // Дополнительный флаг, чтобы отметить конец слова
    current->isEndOfWord = true;
    buildSuffixLinks(root);
}

bool searchWord(Trie* root, const std::string& word) {
    Trie* current = root;
    for (char letter : word) {
        if (current->to.find(letter) == current->to.end()) {
            return false; // Символ не найден, слова нет в боре
        }
        current = current->to[letter];
    }
    // Проверка наличия флага, отмечающего конец слова
    return current->isEndOfWord;
}

void buildTrieFromWords(Trie* root, const std::vector<std::string>& words) {
    for (const std::string& word : words) {
        Trie* current = root;
        for (char letter : word) {
            if (current->to.find(letter) == current->to.end()) {
                current->to[letter] = new Trie();
                current->to[letter]->key = letter;
                current->to[letter]->value = current->value + letter;
            }
            current = current->to[letter];
        }
        // Дополнительный флаг, чтобы отметить конец слова
        current->isEndOfWord = true;
    }
    // Установка суффиксных ссылок
    buildSuffixLinks(root);
}

int main() {
    Trie* tr = new Trie();
    std::vector<std::string> words = { "ab", "bca", "caa"};

    buildTrieFromWords(tr, words);
    printSuffixLinks(tr);
    return 0;
}