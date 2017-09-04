#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>

using KeyVal = std::map<std::string, std::string>;

void str_replace_all(const std::string& search, const std::string& replace, std::string& source) {
    auto pos = source.find(search);
    size_t search_sz = search.size();
    size_t replace_sz = replace.size();
    while (pos != std::string::npos) {
        source.replace(pos, search_sz, replace);
        pos = source.find(search, pos+replace_sz);
    }
}

void split(const std::string& s, std::vector<std::string>& v, char delimiter) {
    size_t start = 0;
    size_t end = s.find_first_of(delimiter, start);
    bool last = false;
    while (!last) {
        if (end == std::string::npos) {
            last = true;
        }
        v.push_back(s.substr(start, end-start));
        if (!last) {
            start = end + 1;
            end = s.find_first_of(delimiter, start);
        }
    }
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> v;
    split(s, v, delimiter);
    return v;
}

struct Tag {
    std::string name;
    KeyVal attributes;
    Tag *parent = nullptr;
    std::map<std::string, Tag*> childs; // std::string child's tag_name

    Tag(std::string tag_name, Tag *parent) : name(tag_name), parent(parent) {}
    void set_attributes(std::string tag_line) {
        std::string unrolled_line = tag_line.substr(1, tag_line.length() - 2);
        std::vector<std::string> elems = split(unrolled_line, ' ');
        auto first_it = elems.begin();
        for (auto it = std::next(first_it); it != elems.end();) {
            std::string key = *it;
            auto equal_sign_it = std::next(it);
            auto value_it = std::next(equal_sign_it);
            attributes[key] = *value_it;
            it = std::next(value_it);
        }
    }
};

bool tag_line_is_open(const std::string& s) {
    auto pos = s.find("/");
    if (pos == std::string::npos) {
        return true;
    }
    return false;
}

bool tag_line_is_close(const std::string& s) {
    return !tag_line_is_open(s);
}

std::string get_tag_name_from_open_tag_line(const std::string& tag_line) {
    std::string unrolled_line = tag_line.substr(1, tag_line.length() - 2);
    std::stringstream ss;
    ss << unrolled_line;
    std::string tag_name;
    ss >> tag_name;
    return tag_name;
}

bool has_attributes(const std::string& tag_line) {
    auto pos = tag_line.find(" ");
    if (pos == std::string::npos) {
        return false;
    }
    return true;
}

bool valid_query(const std::string& query) {
    return query.find("~") != std::string::npos;
}

bool find(Tag *node, std::string query, std::string& result) {
    auto pos = query.find(".");
    std::string tag;
    if (pos == std::string::npos) {
        pos = query.find("~");
    }
    // Deepest
    if (pos == std::string::npos) {
        if (node->attributes.count(query) == 0) {
            return false;
        }
        result = node->attributes[query];
        return true;
    } else {
        tag = query.substr(0, pos);
        if (node->childs.count(tag) == 0) {
            return false;
        }
        return find(node->childs[tag], query.substr(pos + 1), result);
    }
}

int main(int argc, char const *argv[]) {
    /* code */
    std::map<std::string, Tag> tag_map;
    static const std::string not_found = "Not Found!";
    // std::ifstream fin("in.txt");
    unsigned n, q;
    std::cin >> n >> q;
    std::cin.ignore();
    Tag root("root", nullptr);
    Tag *current = &root, *tag;
    std::vector<std::string> queries;
    for (auto i = 0; i < n; i++) {
        std::string tag_line;
        getline(std::cin, tag_line);
        str_replace_all("\"", "", tag_line);
        if (tag_line_is_close(tag_line)) {
            current = current->parent; // Done it, now turn back to it's parent
        } else {
            std::string tag_name = get_tag_name_from_open_tag_line(tag_line);
            tag = new Tag(tag_name, current);
            if (has_attributes(tag_line)) {
                tag->set_attributes(tag_line);
            }
            current->childs[tag->name] = tag;
            current = tag;
        }
    }
    for (auto i = 0; i < q; i++) {
        std::string query;
        getline(std::cin, query);
        queries.push_back(query);
    }
    for (const auto& query: queries) {
        std::string result;
        if (!valid_query(query)) {
            std::cout << not_found << std::endl;
            continue;
        }
        if (!find(&root, query, result)) {
            std::cout << not_found << std::endl;
        } else {
            std::cout << result << std::endl;
        }
    }
    return 0;
}
