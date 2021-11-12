#include <Rcpp.h>
#include <RcppParallel.h>
// 2021-11-12

struct Hckm : public RcppParallel::Worker {
    
    RcppParallel::RMatrix<double> gsbval;   // input data
    RcppParallel::RMatrix<double> dist2;    // input data
    RcppParallel::RVector<double> gk;       // output vector to write to
    
    Hckm(
        Rcpp::NumericMatrix gsbval, 
        Rcpp::NumericMatrix dist2, 
        Rcpp::NumericVector gk
        ): gsbval(gsbval), dist2(dist2), gk(gk) {}
    
    double zLcpp (int c, int k, int m)
    {
        return (gsbval(c,0) * std::exp(-dist2(k,m) / 2 / gsbval(c,1)/ gsbval(c,1)));
    }
    
    void operator()(std::size_t begin, std::size_t end) {
        int cc = gsbval.nrow();
        int kk = dist2.nrow();
        int c, gi,k;
        for (std::size_t m = begin; m < end; m++) {
            for (k=0; k < kk; k++) {
                for (c=0; c < cc; c++) {
                    gi = cc * (kk * m + k) + c;  
                    gk[gi] = zLcpp(c, k, m);
                }
            }
        }
    }
};

// [[Rcpp::export]]
Rcpp::NumericVector makegkPointcpp (
        int grain,
        int ncores,
        Rcpp::NumericMatrix &gsbval, 
        Rcpp::NumericMatrix &dist2
) 
{
    Rcpp::NumericVector gk(gsbval.nrow() * dist2.size()); 
    Hckm hckm (gsbval, dist2, gk);
    if (ncores>1) {
        RcppParallel::parallelFor(0, dist2.ncol(), hckm, grain, ncores);
    }
    else {
        hckm.operator()(0,dist2.ncol());  // for debugging, allows R calls
    }
    return gk;
}