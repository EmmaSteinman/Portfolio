//===========================================================================================
// Colin Smith and Emma Steinman
// 11 October 2017
// huffman.cpp
// Includes the definition and implementation of a Node class
// Uses command line input to compress or decompress files
//===========================================================================================

#include <iostream>
#include <fstream>
#include <sstream>

#include <bitset>
#include <stdio.h>

#include <cstring>
#include <string>
#include <map>

#include "pq.h"

using namespace std;

class Node
{
	public:
		char character;
		int freq;
		
		Node* left;
		Node* right;
		
		bool isLeaf ( void )
		{
			return (left == NULL && right == NULL);
		}
		
		bool operator< (Node c)
		{
			if(freq < c.freq)
				return true;
			else
				return false;
		}
		
		bool operator> (Node c)
		{
			if(freq > c.freq)
				return true;
			else
				return false;
		}
		
		Node ( void )
		{
			character = '\0';
			freq = 0;
			left = NULL;
			right = NULL;
		}
		
		friend ostream& operator<<(ostream &os, Node &node)
		{
			os << "(" << node.character << " " << node.freq << ")";
			return os;
		}
};

//prototypes
MinPriorityQueue<Node> fileToMPQ ( string s, map<char, int> &frequencies);
Node buildHuffmanTree ( map<char, int> frequencies, MinPriorityQueue<Node> &nodes );
void searchHuffmanTree ( map<char, int> frequencies, map<char, string> &huffCodes, Node* z, Node* root, string &s );

//main
int main ( int argc, char* argv[] )
{
	map	<char, int> frequencies;
	map <char, string> huffCodes;
	
	Node *root = new Node;
	
	string inputFile, outputFile; 								// file names
	string s = "";												// used in generating huffman codes and output
	string headerStart, header, out = "";									// used in generating output
	stringstream stm;											// used to write output file header
	
	bool isCompression = false;									// change once decompression is complete
	char c;														// character from file
	int headerSize, r;											// size of header and number of extra bits
	
	if(argc > 4)
	{
		cout << "Error: Too many arguments" << endl << "Proper Syntax: -c|-d input_file output_file" << endl;
		return 0;
	}
	else if(argc < 4)
	{
		cout << "Error: Too few arguments" << endl << "Proper Syntax: -c|-d input_file output_file" << endl;
		return 0;
	}
	
	if(!strcmp(argv[1],"-c"))
		isCompression = true;
	else if(!strcmp(argv[1],"-d"))
		isCompression = false;
	else
	{
		cout << "Error: Improper Syntax" << endl << "Proper Syntax: -c|-d input_file output_file" << endl;
		return 0;
	
	}
	
	inputFile = argv[2];
	outputFile = argv[3];
	
	if(isCompression)											// BEGIN Compression
	{
		ifstream infile(inputFile.c_str());						// open input file
		
		if(infile.is_open())									// check that file was opened
		{
			while(infile.get(c))								// loop to get character frequencies
			{
				frequencies[c]++;								// increment frequency for character c
			}
		}else{
			cout << "Error: Could not open file" << endl;
			return 0;
		}
		infile.close();											// close input file
		
		MinPriorityQueue<Node> nodes(frequencies.size());		// Priority queue of frequencies
		for(map<char, int>::iterator it = frequencies.begin(); it != frequencies.end(); it++) // setup/insert nodes
		{
			Node* n = new Node;									// initialize temporary node
			n->character = it->first;
			n->freq = it->second;
			nodes.insert(n);									// insert node into min priority queue
			//cout << it->first << " " << it->second << endl;
		}
		
		*root = buildHuffmanTree ( frequencies, nodes );		// creates huffman tree from priority queue
		
		searchHuffmanTree(frequencies, huffCodes, root, root, s); // input character huffman code pairs
		
		//cout << endl;
		stm << huffCodes.size();								// beginning of header
		stm << ";";
		headerStart = stm.str();								// set headerStart
		stm.str("");											// reset stm
		
		for(map<char, string>::iterator it = huffCodes.begin(); it != huffCodes.end(); it++) //setup header
		{	
			stm << it->second << it->first;
			//cout << it->first << " " << it->second << endl;
		}
		
		header = stm.str();										// set header
		
		infile.open(inputFile.c_str());							// open input file
		
		if(infile.is_open())
		{
			while(infile.get(c))								// loop to input codes
			{
				out += huffCodes[c];							// append huffman code to output string
			}
			
			s = "";												// reset s to empty
			while(out.size() > 0)								// loop to convert out to bits
			{
				c = 0;											// reset c to NULL
				for(int i = 7; i >= 0; i--)						// loop creates a char byte
				{
					if(out.substr(0,1) == "1")					// adds a 1 to the char byte if there is a 1 in out
					{
						c |= (1 << i);
					}
					if(out.size() == 0)							// gets the number of extra bits
					{
						r = 7 - i;								// r = number of extra bits
						break;
					}
					else
					{
						out = out.substr(1);
					}
				}
				//bitset<8> b(c);
				//cout << b << endl;
				s += c;											// adds char byte to output string
			}	
			
			stm.str("");										// reset stm
			
			stm << r;											// finish headerStart
			stm << ";";
			headerStart += stm.str();
			
			header = headerStart + header;						// finish header
			
			ofstream outfile(outputFile.c_str());				// open/create output file
			int writeSize = s.size();
			s = header + s;
			
			//outfile.write(header.c_str(), header.size());		// write header to output file	
			outfile.write(s.c_str(), s.size() - 1);				// write to output file
		}
	}
	else														// BEGIN Decompression
	{
		ifstream infile(inputFile.c_str());						// open input file
		
		if(infile.is_open())
		{
			while(infile.get(c))								// read first number from header
			{	if(c == ';')
					break;
				s.push_back(c);
			}
			istringstream iss1 (s);
			iss1 >> headerSize;
			
			s = "";												// reset s
			while(infile.get(c))								// read second number from header
			{
				if(c == ';')
					break;
				s.push_back(c);
			}
			istringstream iss2 (s);
			iss2 >> r;
			
			for(int i = 0; i < headerSize; i++)					// loop to read main part of header
			{
				s = "";											// reset s
				while(infile.get(c))							// loop to get codes
				{
					if(c == '0' || c == '1')					// check if code continues
						s.push_back(c);							// append next character of code
					else
						break;
				}
				huffCodes[c] = s;								// add code to huffCodes at character
			}
			
			Node* n = root;										// create node pointer and set to root
			for(map<char, string>::iterator it = huffCodes.begin(); it != huffCodes.end(); it++) // build huff tree
			{
				//cout << it->first << " " << it->second << endl;
				stm.str("");
				stm << it->second;
				s = stm.str();
				
				while(s.size() > 0)								// loop to create tree from huffman map
				{
					if(s.substr(0,1) == "0")
					{
						if(n->left == NULL)
						{
							Node* m = new Node;					// if there is no Node we will make one
							n->left = m;
						}
						n = n->left;
						s = s.substr(1);
					}
					else if(s.substr(0,1) == "1")
					{
						if(n->right == NULL)
						{
							Node* m = new Node;
							n->right = m;
						}
						n = n->right;
						s = s.substr(1);
					}
					else
					{
						cout << "Error: invalid huffman code" << endl;
						return 0;
					}
				}
				n->character = it->first;
				n = root;
			}
			
			n = root;											// reset n to root
			s = "";												// reset s to empty
			
			Node* temp = new Node;								// create temp node pointer
			string s1;
			
			while(!infile.eof())								// convert bits to bit string
			{	
				infile.get(c);
				//bitset<8> b(c);
				//cout << b << endl;
				for(int i = 7; i >= 0; i--)
				{
					if(c & (1 << i))
					{
						s += "1";
					}
					else
					{
						s += "0";
					}
				}
			}
			
			s = s.substr(0, s.size() - r);					// remove trailing bits
			while(s.size() > 0)								// generate characters using the huffman tree
			{
				c = s[0];
				if(n->isLeaf())
				{
					s1.push_back(n->character);
					n = root;
				}
				else if(c == '0')
				{
					n = n->left;
					s = s.substr(1);
				}
				else if(c == '1')
				{
					n = n->right;
					s = s.substr(1);
				}
				else
				{
					cout << "Error: Invalid Encoding" << endl; cout << s << endl;
					return 0;
				}
			}
			s1.push_back(n->character);
			
			ofstream outfile(outputFile.c_str());			// open/create output file
			
			outfile.write(s1.c_str(), s1.size() - 1);		// write to output file
			
		}else{
			cout << "Error: Could not open file" << endl;
			return 0;
		}
		infile.close();
	}
	
	return 0;
}

//===============================================
// creates a min priority queue from a text file
//===============================================
MinPriorityQueue<Node> fileToMPQ ( string fileName, map<char, int> &frequencies )
{
	ifstream file(fileName.c_str());
	
	char c;
	int counter;
	if(file.is_open())
	{
		while(file.get(c))
		{
			counter++;
			frequencies[c]++;
		}
	}
	
	frequencies.erase(frequencies.begin());
	MinPriorityQueue<Node> nodes(frequencies.size());

	for(map<char, int>::iterator it = frequencies.begin(); it != frequencies.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
		Node c;
		c.character = it->first;
		c.freq = it->second;
		nodes.insert(&c);
		//string temp = nodes.toString();
		//cout << temp << endl;
	}
	
	return nodes;
}

//===============================================
// creates a huffman tree from a priority queue
//===============================================
Node buildHuffmanTree ( map<char, int> frequencies, MinPriorityQueue<Node> &nodes )
{
	int n = frequencies.size();
	for(int i = 0; i < n - 1; i++)
	{
		Node* z = new Node;
		z->left = nodes.extractMin();
		z->right = nodes.extractMin();
		if(z->left != NULL)
			z->freq += z->left->freq;
		if(z->right != NULL)
			z->freq += z->right->freq;
		z->character = '\0';
		nodes.insert(z);
	}
	Node *root = nodes.extractMin();
	Node x = *root;
	return x;
}
//===============================================
// creates huffman codes from huffman tree
//===============================================
void searchHuffmanTree ( map<char, int> frequencies, map<char, string> &huffCodes, Node* z, Node* root, string &s )
{
	char c;
	if(z->isLeaf())
	{
		c = z->character;
		huffCodes[c] = s;
	}else{
		if(z->left != NULL)
		{
			s = s + "0";
			searchHuffmanTree(frequencies, huffCodes, z->left, root, s);
		}
		if(z->right != NULL)
		{
			s = s + "1"; 
			searchHuffmanTree(frequencies, huffCodes, z->right, root, s);
		}
	}
	s = s.substr(0,s.size() - 1);
}
