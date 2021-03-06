#include "HTMLParser.h"
#define DEBUG 1
using namespace std;

inline bool IsLink(const string& str) {return regex_match(str, link_re);}
void delTagDfs(Tag* tag)
{
	for(Tag* p = tag -> son(); p != NULL; p = p -> next()) delTagDfs(p);
	delete tag;
}

int output_dfs(Tag *tg,  DFSMODE md, ofstream& oflie){
	int num = 0;
	if(md == LINKMODE){
		if(tg -> attrs.count("href")){
			oflie << tg -> attrs["href"] << endl;
			num++;
		}
	}
	else if(md == TEXTMODE){
		if(DEBUG){
		std::cout << tg->getTagName() << " : " << tg->strs.size() << std::endl;
		}
		for(auto x: tg->strs){
			cout << x;
			oflie << x;
			num++;
		}
	}
	else{
		return -1; //Error
	}
	for(Tag* p = tg->son(); p != nullptr; p = p -> next())
		num += output_dfs(p, md, oflie);
	return num;
}



Tag* Tag::find(const string& tag_name){
	Tag *res = nullptr;
	if(this->tagName == tag_name){
		return this;
	}
	else{
		for(Tag *p = this->son(); p != nullptr; p = p->next()){
			res = p -> find(tag_name);
			if(res != nullptr) return res;
		}
	}
	return res;
}
int Tag::find_all(const string& tag_name, std::vector<Tag*> &v){
	int num = 0;
	if(this->tagName == tag_name){
		num++;
		v.push_back(this);
	}
	for(Tag *p = this->son(); p != nullptr; p = p -> next()){
		num += p->find_all(tag_name, v);
	}
	return num;
}
