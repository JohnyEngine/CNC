#ifndef __STLIMPORTER_H_
#define __STLIMPORTER_H_

#include "Geometry.h"
#include <string>
#include <vector>

/*!\class FileSTL
 * \brief Reads in Stereolithography files.
 * STL is a very widespread file format to exchange geometry data
 * between CAD programms. This class reads a STL file and stores its
 * triangles.
 */

class STLImporter : public Geometry {
	// Constructor/ Destructor
public:
	STLImporter();
	virtual ~STLImporter();

	// Member variables
public:

	//Methods:
public:
	bool ReadFile(const std::string & fileName);
	bool ReadStream(std::istream & stream);
	static void WriteStream(std::ostream & stream, Geometry & g);
private:

	std::string trim(std::string& str);

	std::string mFileName;
	std::string mError;

	bool ReadStreamBinary(std::istream & stream, bool hasRead5Byte = false);
	bool ReadStreamAscii(std::istream & stream, bool hasRead5Byte = false);

	template<typename T>
	void Read(std::istream & stream, T* buffer, std::size_t count = 1);

	std::vector<GeometryPtr> geometry;

};

#endif // __STLIMPORTER_H_
