#include <iostream>
#include <string>

class String {
    private:
        char* s_data;
        int s_len;
    public:
        String() : s_data(nullptr), s_len(0) {}

        String(const char* str) {
            int strLen = strlen(str);
            s_data = new char[strLen + 1];
            s_len = strLen;
        }

        String(const String& str) : String(str.s_data) {}

        String(String&& str) noexcept : s_len(0), s_data(nullptr) {
            swap(*this, str);
        }

        ~String() {
            delete[] s_data;
        }

        String& operator=(const String& a) {
            String temp(a);
            swap(*this, temp);
            return *this;
        }

        String& operator=(String&& a) {
            swap(*this, a);
            return *this;
        }

        


        friend void swap(String& a, String& b) {
            using std::swap;
            swap(a.s_data, b.s_data);
            swap(a.s_len, b.s_len);
        }
};

int main() {

    using std::string;
    string s("hello");
    string s1 = "hello";
    std::cout << s << '\n';
    char c = s[0];
    int sz = s.size();
    string v = std::move(s);
    string l(std::move(s1));

}