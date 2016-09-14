#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <stddef.h>  // defines NULL
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "Helpers.h"
#include "DataLayerAccess.h" // to retrieve the mesh vertices for GetBoundaryMesh()
#include "Analytics.h"
// the format is shared between the QueryManager, the AccessLibrary and th visualiztion client
// so it's located in the AccessLibrary folder
#include "../../AccessLib/AccessLib/BoundaryBinaryMesh.h"

#include "AnalyticsCommon.h"
#include "Simplification.h"
using namespace VELaSSCo;

#pragma message( "WARNING: ")
#pragma message( "WARNING: yarn and hdfs should be in the $PATH and not hard coded in the source.")
#pragma message( "WARNING: look at GetFullHBaseConfigurationFilename() for a similar approach: PathToYarnAndHDFS()")
#pragma message( "WARNING: ")

static std::string demo_simplified_mesh() {
  // This is code from the DemoServer :
  VELaSSCo::BoundaryBinaryMesh::MeshPoint lst_vertices[] = {
    {  1, {  0.0000000000000000e+00,  0.0000000000000000e+00,  3.0000000000000000e+00}},
    {  2, {  0.0000000000000000e+00,  2.5000000000000000e-01,  2.2500000000000000e+00}},
    {  3, { -2.1650634706020355e-01, -1.2500000000000000e-01,  2.2500000000000000e+00}},
    {  4, {  2.1650634706020355e-01, -1.2500000000000000e-01,  2.2500000000000000e+00}},
    {  5, {  0.0000000000000000e+00,  5.0000000000000000e-01,  1.5000000000000000e+00}},
    {  6, { -4.3301269412040710e-01, -2.5000000000000000e-01,  1.5000000000000000e+00}},
    {  7, {  4.3301269412040710e-01, -2.5000000000000000e-01,  1.5000000000000000e+00}},
    {  8, { -1.1780370958149433e-02, -7.9105973243713379e-02,  8.0925619602203369e-01}},
    {  9, {  0.0000000000000000e+00,  7.5000000000000000e-01,  7.5000000000000000e-01}},
    { 10, { -6.4951902627944946e-01, -3.7500000000000000e-01,  7.5000000000000000e-01}},
    { 11, {  6.4951902627944946e-01, -3.7500000000000000e-01,  7.5000000000000000e-01}},
    { 12, { -6.7148506641387939e-01,  3.8768208026885986e-01,  6.7390751838684082e-01}},
    { 13, { -8.9912943757042285e-10, -7.7536416053771973e-01,  6.7390751838684082e-01}},
    { 14, {  6.7148506641387939e-01,  3.8768208026885986e-01,  6.7390751838684082e-01}},
    { 15, { -1.1102230246251565e-16, -2.2204460492503131e-16,  0.0000000000000000e+00}},
    { 16, {  0.0000000000000000e+00,  1.0000000000000000e+00,  0.0000000000000000e+00}},
    { 17, { -8.6602538824081421e-01, -5.0000000000000000e-01,  0.0000000000000000e+00}},
    { 18, {  8.6602538824081421e-01, -5.0000000000000000e-01,  0.0000000000000000e+00}},
    { 19, { -6.4278763532638550e-01,  7.6604443788528442e-01,  0.0000000000000000e+00}},
    { 20, { -9.8480772972106934e-01,  1.7364817857742310e-01,  0.0000000000000000e+00}},
    { 21, { -3.4202015399932861e-01, -9.3969261646270752e-01,  0.0000000000000000e+00}},
    { 22, {  3.4202015399932861e-01, -9.3969261646270752e-01,  0.0000000000000000e+00}},
    { 23, {  9.8480772972106934e-01,  1.7364817857742310e-01,  0.0000000000000000e+00}},
    { 24, {  6.4278763532638550e-01,  7.6604443788528442e-01,  0.0000000000000000e+00}}
  };
  VELaSSCo::BoundaryBinaryMesh::BoundaryQuadrilateral lst_tetrahedra[] = {
    { 4, {  2,  1,  3,  4}},
    { 4, {  3,  2,  4,  7}},
    { 4, {  2,  3,  6,  7}},
    { 4, { 20, 19, 12, 15}},
    { 4, { 24, 23, 14, 15}},
    { 4, { 22, 21, 13, 15}},
    { 4, { 23, 18, 11, 15}},
    { 4, { 19, 16,  9, 15}},
    { 4, { 21, 17, 10, 15}},
    { 4, { 18, 22, 11, 15}},
    { 4, { 17, 20, 10, 15}},
    { 4, { 16, 24,  9, 15}},
    { 4, { 20, 12, 10, 15}},
    { 4, { 22, 13, 11, 15}},
    { 4, { 24, 14,  9, 15}},
    { 4, { 14, 23, 11, 15}},
    { 4, { 13, 21, 10, 15}},
    { 4, { 12, 19,  9, 15}},
    { 4, { 10, 12,  6,  8}},
    { 4, { 10, 12,  8, 15}},
    { 4, {  6, 10,  8, 13}},
    { 4, { 10,  8, 13, 15}},
    { 4, {  8, 13, 15, 11}},
    { 4, {  8, 13, 11,  7}},
    { 4, { 11,  8,  7, 14}},
    { 4, { 11,  8, 14, 15}},
    { 4, {  8,  6, 13,  7}},
    { 4, {  8,  6,  7,  5}},
    { 4, {  8,  6,  5, 12}},
    { 4, {  6,  7,  5,  2}},
    { 4, {  7,  8,  5, 14}},
    { 4, {  9, 14,  5,  8}},
    { 4, {  9, 14,  8, 15}},
    { 4, {  5,  9,  8, 12}},
    { 4, {  9,  8, 12, 15}}
  };
  // we store tetrahedra as quadrilaterals in the BoundaryBinaryMesh
  VELaSSCo::BoundaryBinaryMesh demo_mesh;
  int64_t num_vertices = ( int64_t)( sizeof( lst_vertices) / sizeof( VELaSSCo::BoundaryBinaryMesh::MeshPoint));
  int64_t num_tetrahedra = ( int64_t)( sizeof( lst_tetrahedra) / sizeof( VELaSSCo::BoundaryBinaryMesh::BoundaryQuadrilateral));
  demo_mesh.set( lst_vertices, num_vertices, lst_tetrahedra, num_tetrahedra, VELaSSCo::BoundaryBinaryMesh::STATIC);
  // end of code from DemoServer.cpp
  return demo_mesh.toString();
}

static bool getBoundaryQuadrilateralsAndResultsFromJavaOutput( const char *filename, 
							       std::vector< VELaSSCo::BoundaryBinaryMesh::MeshPoint> &lst_coordinates,
							       std::vector< VELaSSCo::BoundaryBinaryMesh::BoundaryQuadrilateral> &lst_quadrilaterals,
							       std::vector< double> &lst_results) {
 FILE *fi = fopen( filename, "r");
 bool ok = true;

 VELaSSCo::BoundaryBinaryMesh::BoundaryQuadrilateral quadrilateral;
 ssize_t n_read = 0;
 size_t hexa_data_line_size = 64 * 1024;
 char *hexa_data_line = ( char *)malloc( hexa_data_line_size * sizeof( char));
 size_t binary_data_size = 32 * 1024;
 char *binary_data = ( char *)malloc( binary_data_size * sizeof( char));

 // renumber vertices too, as it's ID is the clusterID of the simplification grid
 // and this can be too high
 std::unordered_map< int64_t, int64_t> oldToNewVertexIDMap;
 int64_t newVertexID = 1;
 while ( !feof( fi)) {
   n_read = getline( &hexa_data_line, &hexa_data_line_size, fi);
   if ( n_read == -1) {
     if ( !feof( fi)) {
       DEBUG( "getBoundaryQuadrilateralsFromJavaOutput: error reading MR output file");
       ok = false; 
     }
     break;
   }

   char *separator = strchr( hexa_data_line, '\t');
   char *key = hexa_data_line, *value = NULL;
   size_t key_size = n_read - 1; // the final '\n'
   size_t value_size = 0;
   if ( separator) {
     key_size = separator - hexa_data_line;
     *separator = '\0';
     separator++;
     value = separator;
     value_size = n_read - key_size - 2; // the '\t' and the '\n';
   }

   // process key part:
   if ( !FromHexString( binary_data, binary_data_size, key, key_size)) {
     DEBUG( "getBoundaryQuadrilateralsFromJavaOutput: error translating hexadecimal key string to binary data.");
     ok = false; 
     break;
   }

   // key is MR_CombinedCellAndElementKeys
   int keyType = byteSwap< int>( *( int*)&binary_data[ 0]);
   if ( keyType == 1) { // MR_CELLID
     // coords information is on 'value' field
     int64_t vertexID = byteSwap< int64_t>( *( int64_t *)&binary_data[ 4]); // sizeof( int)
     // the value part
     if ( !FromHexString( binary_data, binary_data_size, value, value_size)) {
       DEBUG( "getBoundaryQuadrilateralsFromJavaOutput: error translating hexadecimal value string to binary data.");
       ok = false; 
       break;
     } 
     double x = byteSwap< double>( *( double*)&binary_data[  0]);
     double y = byteSwap< double>( *( double*)&binary_data[  8]);
     double z = byteSwap< double>( *( double*)&binary_data[ 16]);
     oldToNewVertexIDMap[ vertexID] = newVertexID;
     VELaSSCo::BoundaryBinaryMesh::MeshPoint newVertex = { newVertexID, { x, y, z}};
     newVertexID++;
     lst_coordinates.push_back( newVertex);
   } else if ( keyType == 2) { // MR_TETRAHEDRON
     // key is a MR_SimplifiedTetrahedron i.e. MR_Quadrilateral
     quadrilateral._num_nodes = byteSwap< int>( *( int *)&binary_data[ 4]); // sizeof( int)
     // assert( triangle._num_nodes == 3);
     if ( quadrilateral._num_nodes != 4) {
       // ok = false; //just finished reading to show something ...
       DEBUG( "getBoundaryQuadrilateralsFromJavaOutput: read num_nodes != 4.");
       break;
     }
     quadrilateral._nodes[ 0] = byteSwap< int64_t>( *( int64_t *)&binary_data[  8]); // 2 * sizeof( int)
     quadrilateral._nodes[ 1] = byteSwap< int64_t>( *( int64_t *)&binary_data[ 16]); // sizeof( int) + sizeof( int64_t)
     quadrilateral._nodes[ 2] = byteSwap< int64_t>( *( int64_t *)&binary_data[ 24]); // sizeof( int) + 2 * sizeof( int64_t)
     quadrilateral._nodes[ 3] = byteSwap< int64_t>( *( int64_t *)&binary_data[ 32]); // sizeof( int) + 3 * sizeof( int64_t)
     lst_quadrilaterals.push_back( quadrilateral);
   } else {
     std::ostringstream oss;
     oss << keyType ;
     DEBUG( "getBoundaryQuadrilateralsFromJavaOutput: unknown KeyType " + oss.str());
   }

 } // !feof( fi)
 fclose( fi);

 // now renumber the elements
 for( std::vector< VELaSSCo::BoundaryBinaryMesh::BoundaryQuadrilateral>::iterator it = lst_quadrilaterals.begin();
      it < lst_quadrilaterals.end(); it++) {
   for ( int i = 0; i < 4; i++) {
     int64_t vertexId = it->_nodes[ i];
     std::unordered_map< int64_t, int64_t>::const_iterator it_newVertexID = oldToNewVertexIDMap.find( vertexId);
     if ( it_newVertexID != oldToNewVertexIDMap.end()) {
       it->_nodes[ i] = it_newVertexID->second;
     }
   }
 }

 return ok;
}

static void getModelBoundingCube( const std::string &sessionID, const std::string &modelID,
				  Simplification::Box &bcube_out) {
  // getting bbox: // the global one
  double modelBBox[ 6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  std::string dl_error_str;
  DataLayerAccess::Instance()->calculateBoundingBox( sessionID, modelID, "", 0, NULL, 0, NULL, modelBBox, &dl_error_str);
  
  Simplification::Box bbox;
  bbox.init( modelBBox[ 0], modelBBox[ 1], modelBBox[ 2]);
  bbox.update( modelBBox[ 3], modelBBox[ 4], modelBBox[ 5]);
  bcube_out = bbox.get_centered_bounding_cube();
  Simplification::Point diff = bbox.max() - bbox.min();
  Simplification::Point diff2 = bcube_out.max() - bcube_out.min();
  LOGGER << "    got bounding box:" << std::endl;
  LOGGER << "     ( " << bbox.min().x << ", " << bbox.min().y << ", " << bbox.min().z
	 << ") - ( " << bbox.max().x << ", " << bbox.max().y << ", " << bbox.max().z
	 << ") | ( dx, dy, dz) = ( " << diff.x << ", " << diff.y << ", " << diff.z << ")" << std::endl;
  LOGGER << "       centered cube:" << std::endl;
  LOGGER << "     ( " << bcube_out.min().x << ", " << bcube_out.min().y << ", " << bcube_out.min().z
	 << ") - ( " << bcube_out.max().x << ", " << bcube_out.max().y << ", " << bcube_out.max().z
	 << ") | ( dx, dy, dz) = ( " << diff2.x << ", " << diff2.y << ", " << diff2.z << ")" << std::endl;
}

void AnalyticsModule::calculateSimplifiedMesh( const std::string &sessionID,
					       const std::string &modelID, const std::string &dataTableName,
					       const int meshID, const std::string &elementType,
					       const std::string &analysisID, const double stepValue,
					       const std::string &parameters, // "GridSize=1024;MaximumNumberOfElements=10000000;BoundaryWeight=100.0;"
					       std::string *return_binary_mesh, std::string *return_error_str) {
  bool return_demo_mesh = false;
  if ( return_demo_mesh) {
    *return_binary_mesh = demo_simplified_mesh();
    return;
  }

  // parsing parameters
  Simplification::Parameters simpParam;
  simpParam.fromString( parameters);
  LOGGER << "    simplification parameters read: " << simpParam.toString() << std::endl;

  Simplification::Box bcube;
  getModelBoundingCube( sessionID, modelID, bcube);

  // std::string return_boundary_mesh;
  // DataLayerAccess::Instance()->calculateBoundaryOfAMesh( sessionID, modelID, meshID, elementType, "", 0,
  // 							 &return_boundary_mesh, &dl_error_str);
  // VELaSSCo::BoundaryBinaryMesh boundaryMesh;
  // boundaryMesh.fromString( return_boundary_mesh, VELaSSCo::BoundaryBinaryMesh::STATIC);
  // const VELaSSCo::BoundaryBinaryMesh::MeshPoint *lst_boundary_vertices = boundaryMesh.getLstVertices();
  // const int64_t nv = boundaryMesh.getNumVertices();
  // LOGGER << "    got boundary mesh with " << nv << " vertices" << std::endl;
  // std::vector< int64_t> lstBoundaryNodes;
  // for ( int64_t iv = 0; iv < nv; iv++) {
  //   lstBoundaryNodes.push_back( lst_boundary_vertices[ iv]._id);
  // }
  // boundaryMesh.reset(); // free memory
  // return_boundary_mesh.clear();

  // at the moment only CLI interface:
  // modelID, if it's binary, convert it to 32-digit hexastring:
  char model_ID_hex_string[ 1024];
  std::string cli_modelID = ModelID_DoHexStringConversionIfNecesary( modelID, model_ID_hex_string, 1024);

  // remove local
  // delete local temporary files
  std::string yarn_output_folder = ToLower( "simplified_mesh_" + sessionID + "_" + cli_modelID);
  std::string local_tmp_folder = create_tmpdir();
  std::string local_output_folder = local_tmp_folder + "/" + yarn_output_folder;
  recursive_rmdir( yarn_output_folder.c_str());

  //GetSimplifiedMesh/dist/GetSimplifiedMesh.jar 1 60069901000000006806990100000000 Simulations_Data_V4CIMNE 1 Tetrahedra static
  std::string analytics_program = GetFullAnalyticsQualifier( "GetSimplifiedMesh_Average");

  bool use_yarn = true;//false;;//true;
  // running java:
  int ret_cmd = 0;
  char meshIDstr[ 100];
  sprintf( meshIDstr, "%d", meshID);
  if ( !use_yarn) {
    std::string cmd_line = "java -jar " + analytics_program + " " + GetFullHBaseConfigurationFilename() + " " + 
      sessionID + " " + cli_modelID + " " + dataTableName + " " + meshIDstr + " " + elementType + " static" +
      " \"" + simpParam.toString() + "\" \"" + bcube.toString() + "\"";
    DEBUG( cmd_line);
    ret_cmd = system( cmd_line.c_str());
    local_output_folder = yarn_output_folder;
  } else { 
    // Using yarn:
    // execute and copy to localdir the result's files
    // running Yarn:
    std::string cmd_line = HADOOP_YARN + " jar " + analytics_program + " " + GetFullHBaseConfigurationFilename() + " " + 
      sessionID + " " + cli_modelID + " " + dataTableName + " " + meshIDstr + " " + elementType + " static" +
      " \"" + simpParam.toString() + "\" \"" + bcube.toString() + "\"";
    DEBUG( cmd_line);
    ret_cmd = system( cmd_line.c_str());
    // output in '../simplified_mesh_sessionID_modelID/part-r-00000' but in hdfs
    // error in '../simplified_mesh_sessionID_modelID/error.txt'
    // copy it to local:
    // cmd_line = hadoop_bin + "/hdfs dfs -copyToLocal simplified_mesh .";
    cmd_line = HADOOP_HDFS + " dfs -copyToLocal " + yarn_output_folder + " " + local_tmp_folder;
    ret_cmd = system( cmd_line.c_str());
    if ( ret_cmd == -1) {
      DEBUG( "Is 'yarn' and 'hdfs' in the path?\n");
    }
  }

  // ret_cmd is -1 on error

  // output in '../simplified_mesh_sessionID_modelID/part-r-00000'
  // error in '../simplified_mesh_sessionID_modelID/error.txt'
  char filename[ 8192];
  sprintf( filename, "%s/part-r-00000", local_output_folder.c_str());
  FILE *fi = fopen( filename, "rb");
 
  if (!fi) {
    // try reading error file
    bool errorfile_read = false;
    sprintf( filename, "%s/error.txt", local_output_folder.c_str());
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
    	std::stringstream buffer;
    	buffer << ifs.rdbuf();
    	*return_error_str = buffer.str();
    	errorfile_read = true;
    }
	ifs.close();
    
    if ( !errorfile_read) {
      *return_error_str = std::string( "Problems executing ") + __FUNCTION__ + 
	( use_yarn ? " Yarn" : " Java") + std::string( " job.");
      if ( use_yarn) {
	*return_error_str += std::string( "\nIs 'yarn' and 'hdfs' in the path?");
      }
    }
    return;
  }
  fclose( fi);

  std::string step_error = "";

  std::vector< VELaSSCo::BoundaryBinaryMesh::BoundaryQuadrilateral> lst_quadrilaterals;
  std::vector< VELaSSCo::BoundaryBinaryMesh::MeshPoint> lst_vertices;
  std::vector< double> lst_results;
  bool ok = getBoundaryQuadrilateralsAndResultsFromJavaOutput( filename, lst_vertices, lst_quadrilaterals, lst_results);
  // lst_results will be empty !!! as we're not interpolating any results ...
  if ( !ok) step_error = "error in getBoundaryQuadrilateralsFromJavaOutput";

  VELaSSCo::BoundaryBinaryMesh simplified_mesh;
  if ( ok) {
    simplified_mesh.set( lst_vertices.data(), lst_vertices.size(), lst_quadrilaterals.data(), lst_quadrilaterals.size(), VELaSSCo::BoundaryBinaryMesh::STATIC);
  }
  if ( !ok) step_error = "error in simplified_mesh.set( ...)";

  // verify output:
  if ( !ok || !simplified_mesh.getNumVertices() || !simplified_mesh.getNumQuadrilaterals()) {
    // try reading error file
    bool errorfile_read = false;
    sprintf( filename, "%s/error.txt", local_output_folder.c_str());
/*    fi = fopen( filename, "r");
    if ( fi) {
      const size_t size_buffer = 1024 * 1024;
      char buffer[ size_buffer + 1];
      char *ok = fgets( buffer, size_buffer, fi);
      fclose( fi);
      if ( ok) {
	*return_error_str = std::string( buffer);
	errorfile_read = true;
      }
    }*/
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
    	std::stringstream buffer;
    	buffer << ifs.rdbuf();
    	*return_error_str = buffer.str();
    	errorfile_read = true;
    }
	ifs.close();
		
    if ( !errorfile_read) {
      *return_error_str = std::string( "Problems with ") + FUNCTION_NAME + 
	( use_yarn ? " Yarn" : " Java") + std::string( " results:\n");
      if ( use_yarn) {
	*return_error_str += std::string( "Is 'yarn' and 'hdfs' in the path?\n");
      }
      if ( !ok) {
	*return_error_str += "\treading analytics output file\n";
	*return_error_str += "\tSTEP " + step_error + "\n";
      }
      char tmp[ 200];
      sprintf( tmp, "%"PRIi64, simplified_mesh.getNumVertices());
      *return_error_str += std::string( "\tnumber of vertices = ") + std::string( tmp);
      sprintf( tmp, "%"PRIi64, simplified_mesh.getNumQuadrilaterals());
      *return_error_str += std::string( " number of tetrahedrons = ") + std::string( tmp) + "\n";
    }
  } else {
    std::cout << "simplified mesh has " 
	      << simplified_mesh.getNumQuadrilaterals() << " tetrahedrons and " 
	      << simplified_mesh.getNumVertices() << " vertices." << std::endl;
    *return_binary_mesh = simplified_mesh.toString();
  }

  DEBUG( "Deleting output files ...");
  if ( use_yarn) {
    std::string cmd_line = HADOOP_HDFS + " dfs -rm -r " + yarn_output_folder;
    DEBUG( cmd_line);
    ret_cmd = system( cmd_line.c_str());
    recursive_rmdir( local_tmp_folder.c_str());
  }

  // delete local tmp files ...
  DEBUG( "Deleting temporary files ...");
  recursive_rmdir( yarn_output_folder.c_str());
}


void AnalyticsModule::calculateSimplifiedMeshWithResult( const std::string &sessionID,
							 const std::string &modelID, const std::string &dataTableName,
							 const int meshID, const std::string &elementType,
							 const std::string &analysisID, const double stepValue,
							 const std::string &parameters, // "GridSize=1024;MaximumNumberOfElements=10000000;BoundaryWeight=100.0;"
							 const std::string &resultName,
							 std::string *return_binary_mesh, std::string *return_result_values,
							 std::string *return_error_str) {
  // bool return_demo_mesh = false;
  // if ( return_demo_mesh) {
  //   *return_binary_mesh = demo_simplified_mesh();
  //   return;
  // }

  // parsing parameters
  Simplification::Parameters simpParam;
  simpParam.fromString( parameters);
  LOGGER << "    simplification parameters read: " << simpParam.toString() << std::endl;

  Simplification::Box bcube;
  getModelBoundingCube( sessionID, modelID, bcube);

  ResultInfo resultInfo;
  bool found = DataLayerAccess::Instance()->getResultInfoFromResultName( sessionID, modelID, analysisID, stepValue, resultName, resultInfo);
  if ( !found ) {
    std::stringstream buffer;
    buffer << " result " << resultName << " information not found";
    LOGGER << buffer << std::endl;
    *return_error_str = buffer.str();
    return;
  }
  // get result number from name in resultInfo.resultNumber;

  // at the moment only CLI interface:
  // modelID, if it's binary, convert it to 32-digit hexastring:
  char model_ID_hex_string[ 1024];
  std::string cli_modelID = ModelID_DoHexStringConversionIfNecesary( modelID, model_ID_hex_string, 1024);

  // remove local
  // delete local temporary files
  std::string yarn_output_folder = ToLower( "simplified_mesh_with_result_" + sessionID + "_" + cli_modelID);
  std::string local_tmp_folder = create_tmpdir();
  std::string local_output_folder = local_tmp_folder + "/" + yarn_output_folder;
  recursive_rmdir( yarn_output_folder.c_str());

  //GetSimplifiedMeshWithResult/dist/GetSimplifiedMeshWithResult.jar 1 60069901000000006806990100000000 Simulations_Data_V4CIMNE 1 Tetrahedra static
  std::string analytics_program = GetFullAnalyticsQualifier( "GetSimplifiedMeshWithResult_Average");

  bool use_yarn = true;//false;;//true;
  // running java:
  int ret_cmd = 0;
  char meshIDstr[ 100];
  sprintf( meshIDstr, "%d", meshID);
  if ( !use_yarn) {
    std::string cmd_line = "java -jar " + analytics_program + " " + GetFullHBaseConfigurationFilename() + " " + 
      sessionID + " " + cli_modelID + " " + dataTableName + " " + meshIDstr + " " + elementType + " static" +
      " \"" + simpParam.toString() + "\" \"" + bcube.toString() + "\"";
    DEBUG( cmd_line);
    ret_cmd = system( cmd_line.c_str());
    local_output_folder = yarn_output_folder;
  } else { 
    // Using yarn:
    // execute and copy to localdir the result's files
    // running Yarn:
    std::string cmd_line = HADOOP_YARN + " jar " + analytics_program + " " + GetFullHBaseConfigurationFilename() + " " + 
      sessionID + " " + cli_modelID + " " + dataTableName + " " + meshIDstr + " " + elementType + " static" +
      " \"" + simpParam.toString() + "\" \"" + bcube.toString() + "\"";
    DEBUG( cmd_line);
    ret_cmd = system( cmd_line.c_str());
    // output in '../simplified_mesh_with_result_sessionID_modelID/part-r-00000' but in hdfs
    // error in '../simplified_mesh_with_result_sessionID_modelID/error.txt'
    // copy it to local:
    // cmd_line = hadoop_bin + "/hdfs dfs -copyToLocal simplified_mesh_with_result .";
    cmd_line = HADOOP_HDFS + " dfs -copyToLocal " + yarn_output_folder + " " + local_tmp_folder;
    ret_cmd = system( cmd_line.c_str());
    if ( ret_cmd == -1) {
      DEBUG( "Is 'yarn' and 'hdfs' in the path?\n");
    }
  }

  // ret_cmd is -1 on error

  // output in '../simplified_mesh_with_result_sessionID_modelID/part-r-00000'
  // error in '../simplified_mesh_with_result_sessionID_modelID/error.txt'
  char filename[ 8192];
  sprintf( filename, "%s/part-r-00000", local_output_folder.c_str());
  FILE *fi = fopen( filename, "rb");
 
  if (!fi) {
    // try reading error file
    bool errorfile_read = false;
    sprintf( filename, "%s/error.txt", local_output_folder.c_str());
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
    	std::stringstream buffer;
    	buffer << ifs.rdbuf();
    	*return_error_str = buffer.str();
    	errorfile_read = true;
    }
	ifs.close();
    
    if ( !errorfile_read) {
      *return_error_str = std::string( "Problems executing ") + __FUNCTION__ + 
	( use_yarn ? " Yarn" : " Java") + std::string( " job.");
      if ( use_yarn) {
	*return_error_str += std::string( "\nIs 'yarn' and 'hdfs' in the path?");
      }
    }
    return;
  }
  fclose( fi);

  std::string step_error = "";

  std::vector< VELaSSCo::BoundaryBinaryMesh::BoundaryQuadrilateral> lst_quadrilaterals;
  std::vector< VELaSSCo::BoundaryBinaryMesh::MeshPoint> lst_vertices;
  std::vector< double> lst_results;
  bool ok = getBoundaryQuadrilateralsAndResultsFromJavaOutput( filename, lst_vertices, lst_quadrilaterals, lst_results);
  if ( !ok) step_error = "error in getBoundaryQuadrilateralsFromJavaOutput";

  VELaSSCo::BoundaryBinaryMesh simplified_mesh;
  if ( ok) {
    simplified_mesh.set( lst_vertices.data(), lst_vertices.size(), lst_quadrilaterals.data(), lst_quadrilaterals.size(), VELaSSCo::BoundaryBinaryMesh::STATIC);
  }
  if ( !ok) step_error = "error in simplified_mesh.set( ...)";

  // verify output:
  if ( !ok || !simplified_mesh.getNumVertices() || !simplified_mesh.getNumQuadrilaterals()) {
    // try reading error file
    bool errorfile_read = false;
    sprintf( filename, "%s/error.txt", local_output_folder.c_str());
/*    fi = fopen( filename, "r");
    if ( fi) {
      const size_t size_buffer = 1024 * 1024;
      char buffer[ size_buffer + 1];
      char *ok = fgets( buffer, size_buffer, fi);
      fclose( fi);
      if ( ok) {
	*return_error_str = std::string( buffer);
	errorfile_read = true;
      }
    }*/
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
    	std::stringstream buffer;
    	buffer << ifs.rdbuf();
    	*return_error_str = buffer.str();
    	errorfile_read = true;
    }
	ifs.close();
		
    if ( !errorfile_read) {
      *return_error_str = std::string( "Problems with ") + FUNCTION_NAME + 
	( use_yarn ? " Yarn" : " Java") + std::string( " results:\n");
      if ( use_yarn) {
	*return_error_str += std::string( "Is 'yarn' and 'hdfs' in the path?\n");
      }
      if ( !ok) {
	*return_error_str += "\treading analytics output file\n";
	*return_error_str += "\tSTEP " + step_error + "\n";
      }
      char tmp[ 200];
      sprintf( tmp, "%"PRIi64, simplified_mesh.getNumVertices());
      *return_error_str += std::string( "\tnumber of vertices = ") + std::string( tmp);
      sprintf( tmp, "%"PRIi64, simplified_mesh.getNumQuadrilaterals());
      *return_error_str += std::string( " number of tetrahedrons = ") + std::string( tmp) + "\n";
    }
  } else {
    std::cout << "simplified mesh has " 
	      << simplified_mesh.getNumQuadrilaterals() << " tetrahedrons and " 
	      << simplified_mesh.getNumVertices() << " vertices." << std::endl;
    *return_binary_mesh = simplified_mesh.toString();
  }

  DEBUG( "Deleting output files ...");
  if ( use_yarn) {
    std::string cmd_line = HADOOP_HDFS + " dfs -rm -r " + yarn_output_folder;
    DEBUG( cmd_line);
    ret_cmd = system( cmd_line.c_str());
    recursive_rmdir( local_tmp_folder.c_str());
  }

  // delete local tmp files ...
  DEBUG( "Deleting temporary files ...");
  recursive_rmdir( yarn_output_folder.c_str());
}
