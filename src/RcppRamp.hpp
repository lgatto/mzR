#ifndef RCPP_RAMP_HPP_INCLUDED
#define RCPP_RAMP_HPP_INCLUDED

#include "cramp.hpp"
#include <Rcpp.h>

class RcppRamp {
public:
  RcppRamp();

   /** Opens a mass spec file (mzXML, mzData, etc.) and creates a cRamp object.
    * @param fileName: Name of the msxml file
    * @param declaredScansOnly: suppress RAMP's behavior of creating sparse tables to accomodate unlisted scans
    */
  void open( const char* fileName, bool declaredScansOnly=false );

   /** closes the mzXML file. Releases the memory of the cRamp object. This function allows memory management from R site.
    */
  void close();
  virtual ~RcppRamp();

   /**
    * Returns the filename.
    * @return the filename
    */
  Rcpp::StringVector getFilename (  );

   /**
    * Reads the run information from the mzXML header.
    * @return rampRunInfo* is parsed to a Rcpp::List
    */
  Rcpp::List getRunInfo (  );

   /**
    * Reads the instrument information from the mzXML header.
    * @return rampInstrumentInfo* is parsed to a Rcpp::List
    */
  Rcpp::List getInstrumentInfo();

   /**
    * Reads the scan header info. It reads for one mass spectrum the header information, like ms level, retention time, ion current, ... .
    * @return rampScanInfo* is parsed to a Rcpp::List
    */
  Rcpp::List getScanHeaderInfo ( int whichScan  );

   /**
    * Reads the scan header info. It reads for all mass spectra the header information, like ms level, retention time, ion current, ... .
    * @return rampScanInfo* is parsed to a Rcpp::List
    */
  Rcpp::DataFrame getAllScanHeaderInfo ( );

   /**
    * This function performs a non-sequential parsing operation on an indexed
    * mzXML file to obtain the peak list (i.e. the mass spectrum) for a numbered scan.
    *
    * @param whichScan: Number of the scan we want to read from
    * @return rampPeakList* is parsed to a Rcpp::List. The first list element contains the number of peaks, the second contains a n x 2 matrix with the peak list. 
    */
  Rcpp::List getPeakList ( int whichScan );

   /**
    * This function reads all scans and returns them as a matrix. The number of rows is equal to the 
    * given number of scan numbers. The columns represent equidistant m/z values.
    * mzXML file to obtain the peak list (i.e. the mass spectrum) for a numbered scan.
    *
    * @param whichScan: The scan numbers we want to read from.
    * @param whichMzLow: The lowest m/z value to be returned. 
    * @param whichMzHigh: The highest m/z value to be returned.
    * @param resMz: The resolution in m/z direction.
    * @return The matrix is given back as a Rcpp::NumericMatrix.
    */
  Rcpp::NumericMatrix
  get3DMap ( std::vector<int> scanNumbers,
	     double whichMzLow,
	     double whichMzHigh,
	     double resMz );

  //  getting for the last scan number (not necessarily the number of scans because of missing scans).
  int getLastScan() const;

  /**
   * checks the status of the object.
   */
  bool OK();

private:
  cRamp *ramp;
  Rcpp::List runInfo;
  bool isInCacheRunInfo;
  Rcpp::List instrumentInfo;
  bool isInCacheInstrumentInfo;
  Rcpp::DataFrame allScanHeaderInfo;
  bool isInCacheAllScanHeaderInfo;
  Rcpp::StringVector filename;
};

#endif
