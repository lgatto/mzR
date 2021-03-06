\name{openMSfile}
\alias{openMSfile}
\alias{initializeRamp}
\alias{isInitialized}
\alias{fileName}
\alias{writeMSfile}
\alias{openIDfile}

\title{
  Create and check mzR objects from netCDF, mzXML, mzData or mzML files.
}
\usage{
 openMSfile(filename, backend=c("Ramp", "netCDF", "pwiz"), verbose = FALSE)

 initializeRamp(object)

 isInitialized(object)

 fileName(object)
 
 writeMSfile(object, filename, outformat)

 openIDfile(filename, verbose = FALSE )
}
\arguments{
  \item{filename}{ Path name of the netCDF, mzData, mzXML or mzML file to
    read/write. }
  \item{backend}{ A \code{character} specifiying with backend API to
    use. Currently 'Ramp', 'netCDF'  and 'pwiz' are available.}
  \item{object}{ An instantiated mzR object. }
  \item{verbose}{ Enable verbose output. }
  \item{outformat}{The output format.}
}

\description{
  The \code{openMSfile} constructor will create a new format-specifc
  \code{mzR} object, open 'filename' file and all header information is
  loaded as a Rcpp module and made accessible through the \code{ramp} or \code{pwiz}
  slot of the resulting object.
  
  The \code{writeMSfile} function will write a mzR object (\code{pwiz} backend only)
  into a file. mgf/mzML/mzXML formats are supported.
  
  The \code{openIDfile} constructor will create a new format-specifc
  \code{mzR} object, open 'filename' file and all information is
  loaded as a Rcpp module. The mzid format is supported throught \code{pwiz} backend.

  % If the object was created manually with e.g. new("mzR"), then
  % initializeRamp() will open the given file. An mzR object can be
  % queried, whether it is assigned to a raw file with isInitialized(),
  % and finally fileName(object) will return the path to the file "behind"
  % the mzR object.
}

\author{
  Steffen Neumann, Laurent Gatto, Qiang Kou
}

\examples{
 library(msdata)
 filepath <- system.file("microtofq", package = "msdata")
 file <- list.files(filepath, pattern="MM14.mzML",
                    full.names=TRUE, recursive = TRUE)
  mz <- openMSfile(file, "ramp")
  fileName(mz)
  isInitialized(mz)
  runInfo(mz)
  close(mz)
}
