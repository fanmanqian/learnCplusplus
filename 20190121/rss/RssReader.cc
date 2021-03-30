 ///
 /// @file    RssReader.cc
 /// @author  mfm(2563965485@qq.com)
 /// @date    2020-12-22 20:18:23
 ///
 
#include "RssReader.h"
#include "tinyxml2.h"
#include <iostream>
#include <regex>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using namespace tinyxml2;


void RssReader::parseRss()
{
	RssItem temp_item;
	XMLDocument doc;
	doc.LoadFile("coolshell.xml");
	if(doc.ErrorID()){
		cout << "XML LoadFile Error" << endl;
		return;
	}
	XMLElement * itemNode = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
	while(itemNode){
		XMLElement * titleNode = itemNode->FirstChildElement("title");
		XMLElement * linkNode = itemNode->FirstChildElement("link");
		XMLElement * descriptionNode = itemNode->FirstChildElement("description");
		XMLElement * contentNode = itemNode->FirstChildElement("content:encoded");
		if(titleNode != nullptr && linkNode != nullptr && descriptionNode != nullptr && contentNode!= nullptr) {
			string title(titleNode->GetText());
			temp_item.title = title;
			string link(linkNode->GetText());
			temp_item.link = link;
			string description(descriptionNode->GetText());
			temp_item.description = description;
			string content(contentNode->GetText());
			std::regex re("<.*?>");
			temp_item.content = std::regex_replace(content,re,string(""));
			_rss.push_back(temp_item);
		}
		itemNode = itemNode->NextSiblingElement("item");
	}
}


void RssReader::dump(const string & filename)
{
	int doc_id = 1;
	ofstream ofs(filename);
	for(auto & elem : _rss){
		string each_page = "<doc>";
		each_page.append("\n");
		each_page.append(" <docid>");
		each_page.append(std::to_string(doc_id));
		each_page.append("</docid>");
		each_page.append("\n");
		each_page.append(" <title>");
		each_page.append(elem.title);
		each_page.append("</title>");
		each_page.append("\n");
		each_page.append(" <link>");
		each_page.append(elem.link);
		each_page.append("</link>");
		each_page.append("\n");
		each_page.append(" <description>");
		each_page.append(elem.description);
		each_page.append("</description>");
		each_page.append("\n");
		each_page.append(" <content>");
		each_page.append(elem.content);
		each_page.append("</content>");
		each_page.append("\n");
		each_page.append("</doc>");
		ofs << each_page << endl;
		doc_id += 1;
	}
	ofs.close();
}
