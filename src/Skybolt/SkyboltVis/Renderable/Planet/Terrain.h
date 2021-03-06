/* Copyright 2012-2020 Matthew Reid
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#include "DefaultRootNode.h"
#include "OsgBox2.h"
#include "ShadowHelpers.h"
#include <osg/Texture2D>

#include <boost/optional.hpp>

namespace skybolt {
namespace vis {

osg::ref_ptr<osg::Image> createNormalmapFromHeightmap(const osg::Image& heightmap, const osg::Vec2f& texelWorldSize);

struct TerrainConfig
{
	struct Tile
	{
	protected:
		Tile() {}
		virtual ~Tile() {}
	};

	struct FlatTile : Tile
	{
		osg::Vec2f size;
	};

	struct PlanetTile : public Tile
	{
		Box2d latLonBounds;
		float planetRadius;
	};

	std::shared_ptr<Tile> tile;

	struct DetailMaps
	{
		osg::ref_ptr<osg::Texture2D> attributeMap;
		std::vector<osg::ref_ptr<osg::Texture2D>> albedoDetailMaps;
		osg::ref_ptr<osg::Texture2D> noiseMap;
	};

	osg::ref_ptr<osg::Texture2D> heightMap;
	osg::ref_ptr<osg::Texture2D> normalMap;
	osg::ref_ptr<osg::Texture2D> overallAlbedoMap;

	boost::optional<DetailMaps> detailMaps;

	ShadowMaps shadowMaps;
	osg::ref_ptr<osg::Program> program;
	float heightScale = 65536;
	osg::Vec2f heightMapUvScale = osg::Vec2f(1, 1);
	osg::Vec2f heightMapUvOffset = osg::Vec2f(0, 0);
	osg::Vec2f overallAlbedoMapUvScale = osg::Vec2f(1, 1);
	osg::Vec2f overallAlbedoMapUvOffset = osg::Vec2f(0, 0);
};

class Terrain : public DefaultRootNode
{
public:
	Terrain(const TerrainConfig& config);
	~Terrain();

	osg::Node* getTerrainNode() const { return mNode; }

	void updatePreRender(const RenderContext& context);

private:
	osg::Node* mNode;
};

} // namespace vis
} // namespace skybolt
