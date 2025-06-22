#include "framework/AssetManager.h"

namespace ly
{
	unique<AssetManager> AssetManager::assetManager{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!assetManager)
		{
			assetManager = std::move(unique<AssetManager>{new AssetManager});
		}
		return *assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{

		LOG("LoadTexture called with path: '%s'", path.c_str());
		LOG("Root directory: '%s'", mRootDirectory.c_str());

		std::string fullPath = mRootDirectory + path;
		LOG("Full path: '%s'", fullPath.c_str());


		auto found = mLoadedTextureMap.find(path);
		// Texture already loaded
		if (found != mLoadedTextureMap.end())
		{
			return found->second;
		}
		// Load texture
		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(mRootDirectory + path))
		{
			mLoadedTextureMap.insert({ path, newTexture });
			return newTexture;
		}
		// Bad path
		return shared<sf::Texture> {nullptr};
	}

	void AssetManager::CleanCycle()
	{
		for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
		{
			// Check if AssetManager is only class holding the shared texture
			if (iter->second.unique())
			{
				LOG("Cleaning texture: %s", iter->first.c_str());
				iter = mLoadedTextureMap.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void AssetManager::SetAssetRootDirectoy(const std::string& directory)
	{
		mRootDirectory = directory;
	}

	AssetManager::AssetManager() : mRootDirectory{}
	{

	}
}