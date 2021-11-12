testfn <- function(grain = 1, ncores = 2, parameters = c(0.5, 20)) 
{
    distmat2 <- as.matrix(dist(matrix(seq(20,1000,20), ncol=2)))
    parametermatrix <- matrix(parameters, nrow = 1)
    gk <- makegkPointcpp (
        as.integer(grain), 
        as.integer(ncores),
        parametermatrix, 
        distmat2
        )
    sum(gk)
}
