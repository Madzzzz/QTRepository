#ifndef FIL_H
#define FIL_H

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include "vertex.h"

//! \brief Simple File IO class.

//! This static class consist of functions for reading vertex data from file
//! and writing vertex data to file.
//! The file format is simple. The number of vertices is written in the first line,
//! followed by vertex data, one vertex on each line.
//! The overloaded stream operators of the Vertex class are used.
//! Any existing file with the same name will be overwritten!
//!
//! \author Dag Nylund
//! \date 16/02/02


class Fil
{
public:
    //! \brief write an array of Vertex objects to textfile.

    //! This function creates a textfile withe the specified name and path.
    //! Any existing file with the same name will be overwritten!
    //! The number of vertices is written on the first line
    //! followed by one Vertex on each line.
    //! \param filnavn The filename with path
    //! \param vertices Array of Vertex objects
    //! \param n Number of vertices in array
    static void skriv(std::string filnavn, Vertex vertices[], const int n);

    //! \brief read a textfile with vertex data
    //!
    //! This function opens an existing textfile with the specified name and path
    //! and vertex data stored on the format specified by skriv()
    //! First the number of vertices is read from line one.
    //! Then storage for all vertices is allocated, and the vertices is read one at a time.
    //! \param filnavn The filename with path
    //! \param vertices Pointer to the vertices array
    //! \param n Number of vertices in array
    static void les(std::string filnavn, Vertex *&vertices, GLuint& n);
};

#endif // FILKLASSE_H
