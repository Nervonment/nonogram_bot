#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

void log(std::ostream& os);

int main() {
    std::ifstream is("config.txt");
    if (!is.is_open()) {
        return -1;
    }
    int size, w, h;
    is >> size >> w >> h;
    is.close();
    
    httplib::Client cli("https://www.puzzle-nonograms.com");
    cli.set_keep_alive(true);
    cli.set_connection_timeout(15, 0);
    httplib::Headers headers{
        {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36"},
        {"Content-Type", "application/x-www-form-urlencoded"}
    };
    httplib::Params params{
        {"new", "+++New+Puzzle+++"},
        {"size", std::to_string(size)},
    };
    log(std::cerr);
    auto resp = cli.Post("/", headers, params);
    if (resp->status == 200) {
        std::cerr << "[LOG] successed to get the puzzle." << std::endl;
        log(std::cerr);
        std::string prefix = "var task = '";
        std::string postfix = "'; var loadedId = 0;";
        auto begin = resp->body.find(prefix) + prefix.length();
        auto end = resp->body.find(postfix);
        // puzzle size
        std::cout << w << " " << h << " ";
        for (auto i = begin; i != end; ++i) {
            std::cout << resp->body[i];
        }

        std::string param_key = "name=\"param\" value=\"";
        auto param_pos = resp->body.find(param_key);
        std::cout << " ";
        for (auto i = param_pos + param_key.size(); resp->body[i] != '\"'; ++i) {
            std::cout << resp->body[i];
	    }
    }
}