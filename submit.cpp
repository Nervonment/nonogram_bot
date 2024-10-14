#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <fstream>

int size;
std::string email;

std::string submit(const std::string& param, const std::string& serialize) {
	httplib::Client cli("https://cn.puzzle-nonograms.com");
	httplib::Params params{
		{ "robot", "1" },
		{ "b", "1" },
		{ "size", std::to_string(size) },
		{ "param", param },
		{ "ansH", serialize },
		{ "ready", "+++完成+++" }
	};
	auto res = cli.Post("/", params);
	if (res->status != 200) {
		std::cerr << "[ERR] http POST faild when submitting, status code: " << res->status << std::endl;
		return "";
	}
	std::string ress = res->body;
	std::string solparams_key = "name=\"solparams\" value=\"";
	int i = ress.find(solparams_key);
	if (i > ress.size()) {
		std::cerr << "[ERR] Wrong ans." << std::endl;
		return "";
	}
	std::cerr << "[LOG] solparams found" << std::endl;
	std::string buff = "";
	for (i += solparams_key.size(); ress[i] != '\"'; i++) {
		buff += ress[i];
	}
	return buff;
}

void log(std::ostream& os);

void hall_submit(const std::string& solparams) {
	httplib::Client cli("https://cn.puzzle-nonograms.com");
	httplib::Params params{
		{ "submitscore", "1" },
		{ "solparams", solparams },
		{ "robot", "1" },
		{ "email", email }
	};
    log(std::cerr);
	auto res = cli.Post("/hallsubmit.php", params);
	if (res->status == 302) {
		std::cerr << "[LOG] hall submit returned 302, It's OK." << std::endl;
    	log(std::cerr);
	}
	else {
		std::cerr << "[ERR] hall submit failed, status code: " << res->status << std::endl;
		std::cerr << "[ERR] code 200 means network is OK but your submition isn't correct." << std::endl;
	}
}

int main() {

    std::ifstream is("config.txt");
    if (!is.is_open()) {
        std::cerr << "[ERR] cannot open `config.txt`." << std::endl;
        return -1;
    }
    int w, h;
    is >> size >> w >> h >> email;
    std::string solution;
    std::string param;
    std::cin >> solution;
    std::cin >> param;
	
    std::cerr << "[LOG] solved" << std::endl;
    log(std::cerr);
    
    std::string solparam = submit(param, solution);
	hall_submit(solparam);
}