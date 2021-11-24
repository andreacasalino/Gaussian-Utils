namespace gmm {
    constexpr double PI_GREEK = 3.14159;
    static const double LOG_2_PI = log(2.0 * PI_GREEK);

    V mean(const std::list<const V*>& l);
    
    M covariance(const std::list<const V*>& l, const V& Mean);

    void invertSymmPositive(M& Sigma_inverse, const M& Sigma);

    double evalNormalLogDensity(const GMMcluster& distr, const V& X);

    bool checkCovariance(const M& Cov);
}
