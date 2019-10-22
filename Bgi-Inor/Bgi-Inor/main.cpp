#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::vector<std::string>> get_song_lyrics(std::string path_lyrics);
std::vector<std::string> get_song_words(std::string path_lyrics);
std::vector<std::vector<std::string>> sort_lyrics(std::vector<std::vector<std::string>> lyrics, std::vector<std::string> words);
void print_lyrics(std::vector<std::vector<std::string>> lyrics);

int main(void)
{
	// get lyrics text file path
	std::string file_path = "./lyrics.txt";

	// read song lyrics into multi-dimensional lyrics vector (a vector containing vectors, one line per vector)
	std::vector<std::vector<std::string>> lyrics = get_song_lyrics(file_path);

	// read song words into one vector containing all of the words in the song
	std::vector<std::string> words = get_song_words(file_path);

	// sort words vector
	std::sort(words.begin(), words.end());

	// go through words vector and lyrics vector in parallel, replace current lyrics token with current word
	lyrics = sort_lyrics(lyrics, words);

	// print legible alphabetized lyrics to user
	print_lyrics(lyrics);
}

std::vector<std::vector<std::string>> get_song_lyrics(std::string path_lyrics)
{
	std::vector<std::vector<std::string>> lyrics = std::vector<std::vector<std::string>>();
	std::ifstream infile(path_lyrics);
	std::string line;

	int i = 0;
	while (std::getline(infile, line))
	{
		lyrics.push_back(std::vector<std::string>());
		std::stringstream stringStream(line);
		std::string word;

		while (std::getline(stringStream, word, ' '))
		{
			lyrics[i].push_back(word);
		}
		i++;
	}
	infile.close();

	return lyrics;
}

std::vector<std::string> get_song_words(std::string path_lyrics)
{
	std::vector<std::string> words = std::vector<std::string>();
	std::ifstream infile(path_lyrics);
	std::string line;

	while (std::getline(infile, line))
	{
		std::stringstream stringStream(line);
		std::string word;
		while (std::getline(stringStream, word, ' '))
		{
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			words.push_back(word);
		}
	}
	infile.close();

	return words;
}

std::vector<std::vector<std::string>> sort_lyrics(std::vector<std::vector<std::string>> lyrics, std::vector<std::string> words)
{
	int c = 0;
	for (int i = 0; i < lyrics.size(); i++)
	{
		for (int j = 0; j < lyrics[i].size(); j++)
		{
			lyrics[i][j] = words[c];
			c++;
		}
	}
	return lyrics;
}

void print_lyrics(std::vector<std::vector<std::string>> lyrics)
{
	for (std::vector<std::string> line : lyrics)
	{
		for (std::string word : line)
		{
			std::cout << word << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}