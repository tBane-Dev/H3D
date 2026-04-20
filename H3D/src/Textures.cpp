#include "Textures.hpp"
#include "DebugLog.hpp"

std::string ConvertWideToUtf8(std::wstring wide) {
	return std::string(wide.begin(), wide.end());
}

/////////////////////
// Texture class

Texture::Texture(std::wstring path, bool& loadingStatus) {
	_path = path;
	_texture = std::make_shared<sf::Texture>();
	if (!_texture->loadFromFile(path)) {
		loadingStatus = false;
	}
}

Texture::~Texture() {

}

////////////////////

std::vector<std::shared_ptr<Texture>> textures;


std::shared_ptr<Texture> getTexture(std::wstring path) {
	for (auto& t : textures) {
		if (t->_path == path)
			return t;
	}

	return nullptr;
}

void loadTexture(std::wstring path) {

	bool loadingStatus = true;
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(path, loadingStatus);

	if(loadingStatus)
		textures.push_back(texture);
}

void loadTextures() {

	std::vector<std::wstring> texturePaths;

	// logos
	texturePaths.push_back(L"tex\\logo.png");
	//texturePaths.push_back(L"tex\\logo.png");
	//texturePaths.push_back(L"tex\\logo.png");
	//texturePaths.push_back(L"tex\\logo.png");
	//texturePaths.push_back(L"tex\\logo.png");

	// load all textures
	for (auto& path : texturePaths) {
		loadTexture(path);
	}

	// Loaded textures
	DebugLog(L"Loading textures:");
	for (auto& path : texturePaths) {
		if (getTexture(path)) {
			DebugStat(path);
		}
	}

	// Failed textures
	bool failed = false;
	for (auto& path : texturePaths) {
		if (!getTexture(path)) {
			if (!failed) {
				DebugError(L"Failed to load textures:");
			}
			DebugError(path);
			failed = true;
		}
	}

	if (failed) {
		exit(0);
	}

}
