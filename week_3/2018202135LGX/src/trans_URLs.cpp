#include"crawler.h"

std::string Crawler::trans_URLs(std::string aurl){

    bool if_ = false;

    if(aurl.find("'") == -1 && aurl.find("\"") == -1){   //如果网址两端未加引号的处理

        int temp = aurl.find_first_of("=");

        aurl = aurl.substr(temp + 1, aurl.size() - 1);

        if_ = true;

    }

    std::regex pattern_1("'[^ >]*'");  //单引号匹配

    std::regex pattern_2("\"[^ >]*\"");  //双引号匹配

    std::string::const_iterator iterStart = aurl.begin();

    std::string::const_iterator iterEnd = aurl.end();

    std::string url_result;

    std::string root = current_url;

    std::smatch result;

    while(regex_search(iterStart, iterEnd, result, pattern_1)){

        url_result = result[0];

        iterStart = result[0].second;

    }
    while(regex_search(iterStart, iterEnd, result, pattern_2)){

        url_result = result[0];

        iterStart = result[0].second;

    }

    if(if_) url_result = aurl; 

    if(url_result.find("http") != std::string::npos){

        return url_result;

    }

    if(url_result.back() =='\'' || url_result.back() == '\"'){

        url_result.pop_back();

    }

    if(url_result.front() =='\'' || url_result.front() == '\"'){

        url_result = url_result.substr(1, url_result.size() - 1);

    }

    if(url_result.find("http")  != -1){

        return url_result;
    }

    if(url_result.front() =='/'){   //相对路径前加/的，回到主页

        return host + url_result;

    }

    if(root == host && url_result.front() != '/'){  

        return host + "/" + url_result;

    }

    if(root != host && url_result.front() != '/'){  //相对路径不加 / 的，回退一次

        int temp = root.find_last_of('/');

        root = root.substr(0, temp + 1);
        
        return root + url_result;
    }

    return url_result;
}