//
// Created by kathy on 05.01.25.
//

#ifndef IO_HPP
#define IO_HPP


#include <fstream>
#include <vector>
#include "base.hpp"

inline std::vector<std::string> split(const std::string& s, const std::string& delimiter)
{
    size_t postStart = 0;
    size_t posEnd;
    size_t delimLen = delimiter.length();

    std::string token;
    std::vector<std::string> res;

    while ((posEnd = s.find(delimiter, postStart)) != std::string::npos)
    {
        token = s.substr(postStart, posEnd - postStart);
        postStart = posEnd + delimLen;
        if (!token.empty())
            res.push_back(token);
    }

    res.push_back(s.substr(postStart));
    return res;
}

inline std::vector<edge> readDimacsFormat(const std::string& path)
{
    std::ifstream file;
    std::string line;
    file.open(path);
    std::vector<edge> edgelist;
    while (file.good())
    {
        std::getline(file, line);
        if (line[0] == 'a' || line[0] == 'e')
        {
            // e.g. 'a 1 1016 14'
            std::vector<std::string> tokens = split(line, " ");
            auto u = std::stoi(tokens[1]);
            auto v = std::stoi(tokens[2]);
            auto w = std::stoi(tokens[3]);
            edgelist.push_back(edge(u,v,w));
        }
    }
    file.close();
    return edgelist;
}

inline bool writeEdgeListToDimacsFormat(const std::string& path, std::string instanceName, std::vector<edge>& edgelist)
{
    std::ofstream outfile;
    outfile.open(path, std::ios::trunc);
    outfile << instanceName <<"\n";
    for (edge currentEdge : edgelist)
    {
        outfile << "a "<< currentEdge.v<<" "<< currentEdge.w<<" "<< currentEdge.weight <<"\n";
    }
    outfile.close();
    return true;
}
#endif //IO_HPP
