\name{smooth.construct.tp.smooth.spec}
\alias{smooth.construct.tp.smooth.spec}
\alias{smooth.construct.ts.smooth.spec}
\alias{tprs}
%- Also NEED an `\alias' for EACH other topic documented here.
\title{Penalized thin plate regression splines in GAMs}

\description{\code{\link{gam}} can use isotropic smooths of any number of variables, specified via terms like
\code{s(x,z,bs="tp",m=3)} (or just \code{s(x,z)} as this is the default basis). These terms are based on thin plate 
regression splines. \code{m} specifies the order of the derivatives in the thin plate spline penalty. If \code{m} is 
a vector of length 2 and the second element is zero, then the penalty null space of the smooth is not included in
the smooth.  

 Thin plate regression splines are constructed by starting with the
  basis and penalty for a full thin plate spline and then truncating this basis in
  an optimal manner, to obtain a low rank smoother. Details are given in
  Wood (2003). One key advantage of the approach is that it avoids
  the knot placement problems of conventional regression spline
  modelling, but it also has the advantage that smooths of lower rank
  are nested within smooths of higher rank, so that it is legitimate to
  use conventional hypothesis testing methods to compare models based on
  pure regression splines. Note that the basis truncation does not change the 
  meaning of the thin plate spline penalty (it penalizes exactly what it 
  would have penalized for a full thin plate spline). 

 The t.p.r.s. basis and penalties can become expensive to
  calculate for large datasets. For this reason the default behaviour is to
  randomly subsample \code{max.knots} unique data locations if there are more than \code{max.knots}
  such, and to use the sub-sample for basis construction. The sampling is
  always done with the same random seed to ensure repeatability (does not
  reset R RNG). \code{max.knots} is 2000, by default. Both seed and
  \code{max.knots} can be modified using the \code{xt} argument to \code{s}.
   Alternatively the user can supply knots from which to construct a basis. 

 The \code{"ts"} smooths are t.p.r.s. with the penalty modified so that the term is shrunk to zero 
for high enough smoothing parameter, rather than being shrunk towards a function in the 
penalty null space (see details).
 
}

\usage{
\method{smooth.construct}{tp.smooth.spec}(object, data, knots)
\method{smooth.construct}{ts.smooth.spec}(object, data, knots)
}

\arguments{ 
\item{object}{a smooth specification object, usually generated by a term \code{s(...,bs="tp",...)} or 
      \code{s(...,bs="ts",...)}}

\item{data}{a list containing just the data (including any \code{by} variable) required by this term, 
            with names corresponding to \code{object$term} (and \code{object$by}). The \code{by} variable 
            is the last element.} 

\item{knots}{a list containing any knots supplied for basis setup --- in same order and with same names as \code{data}. 
             Can be \code{NULL}}

}

\value{ An object of class \code{"tprs.smooth"} or \code{"ts.smooth"}. In addition to the usual elements of a 
smooth class documented under \code{\link{smooth.construct}}, this object will contain:
\item{shift}{A record of the shift applied to each covariate in order to center it around zero and 
avoid any co-linearity problems that might otehrwise occur in the penalty null space basis of the term. }
\item{Xu}{A matrix of the unique covariate combinations for this smooth (the basis is constructed by first stripping 
out duplicate locations).}
\item{UZ}{The matrix mapping the t.p.r.s. parameters back to the parameters of a full thin plate spline.}
\item{null.space.dimension}{The dimension of the space of functions that have zero wiggliness according to the 
wiggliness penalty for this term.}
}

\details{ The default basis dimension for this class is \code{k=M+k.def} where \code{M} is the null space dimension 
(dimension of unpenalized function space) and \code{k.def} is 8 for dimension 1, 27 for dimension 2 and 100 for higher dimensions. 
This is essentially arbitrary, and should be checked, but as with all penalized regression smoothers, results are statistically 
insensitive to the exact choise, provided it is not so small that it forces oversmoothing (the smoother's 
degrees of freedom are controlled primarily by its smoothing parameter).

The default is to set \code{m} (the order of derivative in the thin plate spline penalty) to the smallest value satisfying \code{2m > d+1} where \code{d} if the number of covariates of the term: this yields `visually smooth' functions. In any case \code{2m>d} must be satisfied. 


The constructor is not normally called directly, but is rather used internally by \code{\link{gam}}. 
To use for basis setup it is recommended to use \code{\link{smooth.construct2}}.  

For these classes the specification \code{object} will contain
information on how to handle large datasets in their \code{xt} field. The default is to randomly
subsample 2000 `knots' from which to produce a tprs basis, if the number of
unique predictor variable combinations in excess of 2000. The default can be
modified via the \code{xt} argument to \code{\link{s}}. This is supplied as a
list with elements \code{max.knots} and \code{seed} containing a number
to use in place of 2000, and the random number seed to use (either can be
missing). 

For these bases \code{knots} has two uses. Firstly, as mentioned already, for large datasets 
the calculation of the \code{tp} basis can be time-consuming. The user can retain most of the advantages of the t.p.r.s. 
approach by supplying  a reduced set of covariate values from which to obtain the basis - 
typically the number of covariate values used will be substantially 
smaller than the number of data, and substantially larger than the basis dimension, \code{k}. This approach is 
the one taken automatically if the number of unique covariate values (combinations) exceeds \code{max.knots}.
The second possibility 
is to avoid the eigen-decomposition used to find the t.p.r.s. basis altogether and simply use 
the basis implied by the chosen knots: this will happen if the number of knots supplied matches the 
basis dimension, \code{k}. For a given basis dimension the second option is 
faster, but gives poorer results (and the user must be quite careful in choosing knot locations).


The shrinkage version of the smooth, eigen-decomposes the wiggliness penalty matrix, and sets its zero eigenvalues to small 
multiples of the smallest strictly positive eigenvalue. The penalty is then set to the matrix with eigenvectors corresponding 
to those of the original penalty, but eigenvalues set to the peturbed versions. This penalty matrix has full rank and shrinks 
the curve to zero at high enough smoothing parameters.

}

\references{
Wood, S.N. (2003) Thin plate regression splines. J.R.Statist.Soc.B 65(1):95-114
}

\author{ Simon N. Wood \email{simon.wood@r-project.org}}

\examples{
## see ?gam
}
\keyword{models} \keyword{regression}%-- one or more ..


