testfn <- function(grain = 1, ncores = 2, tiny = FALSE) 
{
    message ("Package leaktest ", packageVersion('leaktest'))
    if (tiny) 
        Sys.setenv(RCPP_PARALLEL_BACKEND = "tinythread")
    else
        Sys.setenv(RCPP_PARALLEL_BACKEND = "tbb")
    
    # fake some data
    distmat2 <- as.matrix(dist(matrix(seq(20,1000,20), ncol=2)))
    parametermatrix <- matrix(c(0.5, 20), nrow = 1)
    gk <- makegkPointcpp (
        as.integer(grain), 
        as.integer(ncores),
        parametermatrix, 
        distmat2
        )
    sum(gk)
}
