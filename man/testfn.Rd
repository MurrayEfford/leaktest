\name{testfn}
\alias{testfn}

\title{Fn for leak test}

\description{

Calls C++ function makegkPointcpp with arbitrary (fake) data

}

\usage{

testfn(grain = 1, ncores = 2, tiny = FALSE)

}

\arguments{
  \item{grain}{integer}
  \item{ncores}{integer}
  \item{tiny}{logical}
}

\value{

Meaningless sum of probabilities gk.

If \code{tiny} then tinythread isused instead of TBB.

}

\examples{

testfn()

}
