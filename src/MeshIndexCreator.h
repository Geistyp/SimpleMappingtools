/*
 *	author:geistyp
 */
#pragma once

#include "ofMain.h"

class MeshIndexCreator
{
public:

	static int getIndex(int x, int y, int c)
	{
		return y*c + x;
	}

	static vector<unsigned int> createTriangleMeshIndex(int gridx, int gridy)
	{
		vector<unsigned int> index;
		if ( gridx < 2 || gridy < 2 ) return index;

		int col = gridx + 1;
		int row = gridy + 1;

		for ( int j = 0; j < row; j++ ) 
		{
			if ( (j+1) == row ) break;			

			if ( j%2 == 0 )	// odd
			{
				int i = 0;
				for ( ; i < col; i++ )
				{
					index.push_back(getIndex(i, j, col));
					index.push_back(getIndex(i, j+1, col));
				}
				index.push_back(getIndex(i-1, j+1, col));
			}
			else			// even
			{
				int i = (col-1);
				for ( ; i >= 0; i-- )
				{
					index.push_back(getIndex(i, j, col));
					index.push_back(getIndex(i, j+1, col));
				}
				index.push_back(getIndex(i+1, j+1, col));
			}
		}

		return index;
	}

};