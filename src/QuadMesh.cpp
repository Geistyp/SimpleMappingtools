#include "QuadMesh.h"


QuadMesh::QuadMesh(void)
{
}


QuadMesh::~QuadMesh(void)
{
}

void QuadMesh::create(int x, int y, int w, int h, int res)
{
	ofVec2f offset(x, y);
	vertex_[0] = ofVec2f(0, 0); vertex_[1] = ofVec2f(w, 0);
	vertex_[2] = ofVec2f(w, h); vertex_[3] = ofVec2f(0, h);
	for( int i = 0; i < 4; i++ )	vertex_[i] += offset;

	resolution_ = res;

	/*
	 *	ofMesh default render is OF_PRIMITIVE_TRIANGLES, 
	 *	OF_PRIMITIVE_TRIANGLE_STRIP will have less indices
	 */
	mesh_.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	createMesh();
	
}
//////////////////////////////////////////////////////////////////////////

void QuadMesh::createMesh()
{
	mesh_.clear();
	for ( int i = 0; i <= resolution_; i++ )	// y
	{
		for ( int j = 0; j <= resolution_; j++ )	// x
		{
			ofVec2f pt = (vertex_[0] + (vertex_[3]-vertex_[0])*(float)i/resolution_)
				+ (
				(vertex_[1]-(vertex_[1]-vertex_[2])*(float)i/resolution_)
				-(vertex_[0] + (vertex_[3]-vertex_[0])*(float)i/resolution_)
				)*(float)j/resolution_;

			ofVec3f p3t = ofVec3f(pt.x, pt.y, 0);
			mesh_.addVertex(p3t);
			// [0-1] normal texture coords
			ofVec2f t2t = ofVec2f((float)j/resolution_, (float)i/resolution_);
			mesh_.addTexCoord(t2t);
		}
	}
	vector<unsigned int> index = MeshIndexCreator::createTriangleMeshIndex(resolution_, resolution_);
	mesh_.addIndices(index);
}

void QuadMesh::updateMesh()
{
	for ( int i = 0; i <= resolution_; i++ )	// y
	{
		for ( int j = 0; j <= resolution_; j++ )	// x
		{
			ofVec2f pt = (vertex_[0] + (vertex_[3]-vertex_[0])*(float)i/resolution_)
				+ (
				(vertex_[1]-(vertex_[1]-vertex_[2])*(float)i/resolution_)
				-(vertex_[0] + (vertex_[3]-vertex_[0])*(float)i/resolution_)
				)*(float)j/resolution_;

			ofVec3f p3t = ofVec3f(pt.x, pt.y, 0);
			mesh_.setVertex(i*(resolution_+1)+j, p3t);
		}
	}
}