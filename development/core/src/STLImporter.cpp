#include "STLImporter.h"

#include <stdint.h>
#include <fstream>
#include <tchar.h>
#include <assert.h>


#define LogMessage(message)

STLImporter::STLImporter()
{
}

STLImporter::~STLImporter()
{
}



bool STLImporter::ReadFile(const std::string & fileName)
{
	mError.clear();
	this->mFileName = fileName;
	std::ifstream inStream(fileName);

	LogMessage(std::string(_T("Opening File:") + fileName));

	if(!inStream.is_open()){
		mError += _T("STL File ") + fileName + _T(": File won't open.\n");
		return false;
	}

	return ReadStream(inStream);
}

bool STLImporter::ReadStream(std::istream & stream)
{
	// Find the header of the STL file:
	char header[6];
	header[5] = 0;

	if(!stream.read(header, 5)){
		mError += _T("STL File ") + mFileName + _T(": File contains no header.\n");
		return false;
	}
	if(strncmp(header, "solid", 5) == 0){

		// Make sure, that number are written with a dot and not a comma.
		setlocale(LC_ALL, "C");
		bool flag = ReadStreamAscii(stream, true);
		setlocale(LC_ALL, "");

		return flag;
	}else{
		return ReadStreamBinary(stream, true);
	}

}

template<typename T>
void STLImporter::Read(std::istream & stream, T* buffer, std::size_t count)
{
	if (buffer)
	{
		T* data = buffer;

		for (size_t i = 0; i < count; i++)
		{
			if (!stream)
				break;

			stream >> *data;

			data += sizeof(T);
		}
	}
}

bool STLImporter::ReadStreamBinary(std::istream & stream, bool hasRead5Byte)
{
//	wxString temp;
	std::istream& binaryStream(stream);

	char header[81];
	header[80] = 0;
	if(hasRead5Byte){
		binaryStream.read(header, 80 - 5);
	}else{
		binaryStream.read(header, 80);
	}
	if(stream.eof()){
		mError += _T("STL File ") + mFileName + _T(": File contains no header.\n");
		return false;
	}
	// Set up a new geometry object.
	Geometry* g = new Geometry();
	g->name = mFileName;
	g->color.set(color);
	g->colorNewObjects.set(color);

	geometry.clear(); // Clear the old geometry and
	geometry.push_back(GeometryPtr(g)); //insert the new one.
	size_t nGeometry = geometry.size() - 1;
	assert(nGeometry==0);

	// Binary STL File
	uint32_t nrOfTriangles = 0;

	Read(binaryStream, &nrOfTriangles);

	if(stream.eof()){
		mError += _T("STL File ") + mFileName + _T(": File to short!");
		return false;
	}

	uint32_t i;
	unsigned char j;
	float coord[12];

	assert(sizeof(float)==4);

	uint16_t attribute;

	Triangle tri;
	for(i = 0; i < nrOfTriangles; i++){
		Read(binaryStream, coord, 12);

		if(stream.eof()){
			mError += _T("STL File ") + mFileName + _T(": File to short!");
			return false;
		}

		Read(binaryStream, &attribute);

		if (stream.eof()){
			mError += _T("STL File ") + mFileName + _T(": File to short!");
			return false;
		}

		FVector3 color;
		if(attribute & (1 << 15)){
			color.x = (float) ((attribute >> 0) & 31) / 31.0;
			color.y = (float) ((attribute >> 5) & 31) / 31.0;
			color.z = (float) ((attribute >> 10) & 31) / 31.0;
		}else{
			color.set(geometry[nGeometry]->colorNewObjects);
		}

		for(j = 0; j < 3; j++){
			tri.p[j].x = coord[3 + j * 3];
			tri.p[j].y = coord[4 + j * 3];
			tri.p[j].z = coord[5 + j * 3];
			tri.n[j].x = coord[0];
			tri.n[j].y = coord[1];
			tri.n[j].z = coord[2];
			tri.c[j].set(color);
		}

		// The normal vectors seem to be defect for some files.
		// if(false)... = Calculate normals
		// if(true)...  = Use normals from file
//		if(false){
//			geometry[nGeometry].AddTriangleWithNormals(tri.p[0], tri.p[1],
//					tri.p[2], tri.n[0], tri.n[0], tri.n[0]);
//		}else{
//			geometry[nGeometry].AddTriangle(tri.p[0], tri.p[1], tri.p[2]);
//		}

		geometry[nGeometry]->AddTriangle(tri, false);

		//			if(i <= 1){
		//				LogMessage(wxString::Format(_T("n: %.1f %.1f %.1f"),
		//						tri->n.x, tri->n.y, tri->n.z));
		//				for(j = 0; j < 3; j++)
		//
		//					LogMessage(wxString::Format(_T("p: %.1f %.1f %.1f"),
		//							tri->p[j].x, tri->p[j].y, tri->p[j].z));
		//			}
	}
	return true;
}

void STLImporter::WriteStream(std::ostream & stream, Geometry & g)
{
#if 0
	std::ostream& binaryStream(stream);

	unsigned char header[81] =
			"Generated by CAMBOT.                                                            ";

	binaryStream.Write8(header, 80);
	binaryStream.Write32(wxUint32(g.triangles.size()));
	for (int n = 0; n < g.triangles.size(); n++){
		float coord[12];
		coord[0] = g.triangles[n].n[0].x;
		coord[1] = g.triangles[n].n[0].y;
		coord[2] = g.triangles[n].n[0].z;
		coord[3] = g.triangles[n].p[0].x;
		coord[4] = g.triangles[n].p[0].y;
		coord[5] = g.triangles[n].p[0].z;
		coord[6] = g.triangles[n].p[1].x;
		coord[7] = g.triangles[n].p[1].y;
		coord[8] = g.triangles[n].p[1].z;
		coord[9] = g.triangles[n].p[2].x;
		coord[10] = g.triangles[n].p[2].y;
		coord[11] = g.triangles[n].p[2].z;
		binaryStream.Write32((uint32_t*) coord, 12);
		uint16_t col = (1 << 15); // bit 15 set = color valid
		col |= ((int) floor(g.triangles[n].c[0].z * 32)) & 31;
		col |= (((int) floor(g.triangles[n].c[0].y * 32)) & 31) << 5;
		col |= (((int) floor(g.triangles[n].c[0].x * 32)) & 31) << 10;
		binaryStream.Write16(col);
	}
#endif
}

std::string STLImporter::trim(std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

bool STLImporter::ReadStreamAscii(std::istream & stream, bool hasRead5Byte)
{

	std::istream& textStream(stream);
	std::string word, line;

	getline(textStream, word);
	trim(word);

	if (hasRead5Byte)
		word = _T("solid ");


	if(!word.find_first_of(_T("solid"))){
		mError += _T("STL Text File ") + mFileName + _T(": Incorrect file.");
		return false;
	}

	float normal[3];
	float coord[12];
	Triangle tri;
	unsigned int n;
	unsigned char j, m;
	std::string temp;

	geometry.clear();

	while ((temp = word.substr(word.find_first_of(_T("solid")))).size()){
		trim(temp);

		// Set up a new geometry object.
		Geometry* g = new Geometry();
		if(temp.empty()){
			g->name = mFileName;
		}else{
			g->name = temp;
		}
		g->color.set(color);
		g->colorNewObjects.set(color);
		geometry.push_back(GeometryPtr(g));
		n = geometry.size() - 1;

		textStream >> word;
		trim(word);
		while(word.compare(_T("facet")) == 0){
			textStream >> word;
			trim(word);
			if (word.compare(_T("normal")) == 0){
				textStream >> normal[0] >> normal[1] >> normal[2];

			}else{
				normal[0] = normal[1] = normal[2] = 0.0;
			}
			textStream >> word;
			trim(word);
			if (word.compare(_T("outer")) != 0){
				mError += _T(
					"STL Text File ") + mFileName + _T(": 'outer' missing.");
				return false;
			}
			textStream >> word;
			trim(word);
			if (word.compare(_T("loop")) != 0){
				mError += _T(
					"STL Text File ") + mFileName + _T(": 'loop' missing.");
				return false;
			}
			for(m = 0; m < 3; m++){
				textStream >> word;
				trim(word);
				if (word.compare(_T("vertex")) != 0){
					mError +=
						_T("STL Text File ") + mFileName + _T(": 'vertex' missing.");
					return false;
				}
				textStream >> coord[m * 3 + 0] >> coord[m * 3 + 1]
						>> coord[m * 3 + 2];
			}
			textStream >> word;
			trim(word);
			if (word.compare(_T("endloop")) != 0){
				mError +=
					_T("STL Text File ") + mFileName + _T(": 'endloop' missing.");
				return false;
			}
			textStream >> word;
			trim(word);
			if (word.compare(_T("endfacet")) != 0){
				mError +=
					_T("STL Text File ") + mFileName + _T(": 'endfacet' missing.");
				return false;
			}

			for(j = 0; j < 3; j++){
				tri.p[j].x = coord[0 + j * 3];
				tri.p[j].y = coord[1 + j * 3];
				tri.p[j].z = coord[2 + j * 3];
				tri.n[j].x = normal[0];
				tri.n[j].y = normal[1];
				tri.n[j].z = normal[2];
				tri.c[j].set(geometry[n]->colorNewObjects);
			}

			// The normal vectors seem to be defect for some files.
			// if(false)... = Calculate normals
			// if(true)...  = Use normals from file
			geometry[n]->AddTriangle(tri, false);
//			if(false){
//				geometry[n].AddTriangleWithNormals(tri.p[0], tri.p[1], tri.p[2],
//						tri.n[0], tri.n[0], tri.n[0]);
//			}else{
//				geometry[n].AddTriangle(tri.p[0], tri.p[1], tri.p[2]);
//			}

			textStream >> word;
			trim(word);
		}
		if (word.compare(_T("endsolid")) != 0){
			mError += _T(
				"STL Text File ") + mFileName + _T(": 'endsolid' missing.");
			return false;
		}

		getline(textStream, word);
		trim(word);
		if(!word.find_first_of(_T("solid"))) 
		{
			getline(textStream, word);
			trim(word);
		}
	}

	return true;
}
