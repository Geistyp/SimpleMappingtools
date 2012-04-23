#include "BezierMesh.h"

#include "MeshIndexCreator.h"

BezierMesh::BezierMesh(void)
{
}


BezierMesh::~BezierMesh(void)
{
}

void BezierMesh::create(int x, int y, int w, int h, int res)
{
	ofVec2f offset(x, y);
	vertex_[0] = ofVec2f(0, 0);	vertex_[1] = ofVec2f(w, 0);
	vertex_[2] = ofVec2f(w, h);	vertex_[3] = ofVec2f(0, h);

	control_[0] = ofVec2f(0, .33*h); control_[1] = ofVec2f(.33*w, 0);
	control_[2] = ofVec2f(.67*w, 0); control_[3] = ofVec2f(w, .33*h);
	control_[4] = ofVec2f(w, .67*h); control_[5] = ofVec2f(.67*w, h);
	control_[6] = ofVec2f(.33*w, h); control_[7] = ofVec2f(0, .67*h);

	for ( int i = 0; i < 4; i++ ) vertex_[i] += offset;
	for ( int i = 0; i < 8; i++ ) control_[i] += offset;

	this->resolution_ = res;

	texture_width_ = 1.0; 
	texture_height_ = 1.0;
	/*
	 *	ofMesh default render is OF_PRIMITIVE_TRIANGLES, 
	 *	OF_PRIMITIVE_TRIANGLE_STRIP will have less indices
	 */
	mesh_.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	createMesh();
}

void BezierMesh::createMesh()
{
	mesh_.clear();
	for ( int i = 0; i <= resolution_; i++ )
	{
		for ( int j = 0; j <= resolution_; j++ )
		{
			float k = (float)i/resolution_;
			ofVec2f sp = ofBezierPoint(vertex_[0], control_[0], control_[7], vertex_[3], k);
			ofVec2f ep = ofBezierPoint(vertex_[1], control_[3], control_[4], vertex_[2], k);

			ofVec2f pt = ofBezierPoint(sp, 
				(control_[1] - control_[6])*(1.0 - k) + control_[6], 
				(control_[2] - control_[5])*(1.0 - k) + control_[5],
				ep, 
				(float)j/resolution_
				);
			ofVec3f p3t = ofVec3f(pt.x, pt.y, 0);
			mesh_.addVertex(p3t);
			// [0-1] normal texture coords
			ofVec2f t2t = ofVec2f((float)j/resolution_, (float)i/resolution_);
			mesh_.addTexCoord(t2t);
		}
	}
	vector<unsigned int> index = MeshIndexCreator::createTriangleMeshIndex(resolution_, resolution_);
	mesh_.addIndices(index);

	ResetTextureCoords(texture_height_, texture_width_);
	/*
	 *	not commit bTexCoordsChanged so call twice
	 */
	ResetTextureCoords(texture_height_, texture_width_);
}

void BezierMesh::updateMesh()
{
	for ( int i = 0; i <= resolution_; i++ )
	{
		for ( int j = 0; j <= resolution_; j++ )
		{
			float k = (float)i/resolution_;
			ofVec2f sp = ofBezierPoint(vertex_[0], control_[0], control_[7], vertex_[3], k);
			ofVec2f ep = ofBezierPoint(vertex_[1], control_[3], control_[4], vertex_[2], k);

			ofVec2f pt = ofBezierPoint(sp, 
				(control_[1] - control_[6])*(1.0 - k) + control_[6], 
				(control_[2] - control_[5])*(1.0 - k) + control_[5],
				ep, 
				(float)j/resolution_
				);
			ofVec3f p3t = ofVec3f(pt.x, pt.y, 0);
			mesh_.setVertex(i*(resolution_+1)+j, p3t);
		}
	}
}

void BezierMesh::ResetTextureCoords(float w, float h)
{
	texture_width_ = w; 
	texture_height_ = h;
	for ( int i = 0; i <= resolution_; i++ )
	{
		for ( int j = 0; j <= resolution_; j++ )
		{
			ofVec2f t2t = ofVec2f((float)j/resolution_*texture_width_, (float)i/resolution_*texture_height_);
			mesh_.setTexCoord(i*(resolution_+1)+j, t2t);
		}
	}
}
