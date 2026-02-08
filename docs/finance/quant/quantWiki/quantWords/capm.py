"""CAPM utilities

Functions:
- returns_from_prices(prices)
- excess_returns(returns, risk_free)
- estimate_beta(asset_excess, market_excess)
- capm_expected_return(beta, market_premium, risk_free=0.0)

The module includes a small `_demo()` that simulates data and prints estimation results.
"""

import math
from typing import Dict

import numpy as np


def returns_from_prices(prices) -> np.ndarray:
	"""Compute simple returns from a price series.

	Accepts array-like (list, numpy array or pandas Series). Returns 1-D numpy array
	of period simple returns: r_t = P_t / P_{t-1} - 1
	"""
	arr = np.asarray(prices)
	if arr.ndim != 1:
		raise ValueError("prices must be a 1-D sequence")
	return arr[1:] / arr[:-1] - 1


def excess_returns(returns, risk_free) -> np.ndarray:
	"""Subtract risk-free rate from returns.

	- If `risk_free` is scalar, it is subtracted from every return.
	- If `risk_free` is array-like, it must match length of `returns`.
	"""
	r = np.asarray(returns)
	rf = np.asarray(risk_free)
	if rf.ndim == 0:
		return r - float(rf)
	rf = np.asarray(rf)
	if rf.shape != r.shape:
		raise ValueError("risk_free must be scalar or same shape as returns")
	return r - rf


def estimate_beta(asset_excess, market_excess) -> Dict[str, float]:
	"""Estimate CAPM parameters by OLS: asset_excess = alpha + beta * market_excess + eps.

	Returns a dict with keys: alpha, beta, se_alpha, se_beta, t_alpha, t_beta, r2, n
	"""
	y = np.asarray(asset_excess, dtype=float)
	x = np.asarray(market_excess, dtype=float)
	if y.shape != x.shape:
		raise ValueError("asset_excess and market_excess must have same shape")
	n = y.size
	if n < 3:
		raise ValueError("need at least 3 observations to estimate")

	X = np.column_stack((np.ones(n), x))
	coef, residuals, rank, s = np.linalg.lstsq(X, y, rcond=None)
	alpha, beta = float(coef[0]), float(coef[1])

	# residuals from the fitted model
	y_hat = X.dot(coef)
	res = y - y_hat
	sse = float(np.sum(res ** 2))
	sst = float(np.sum((y - np.mean(y)) ** 2))
	r2 = 1.0 - sse / sst if sst > 0 else float('nan')

	# estimate variance and standard errors
	k = X.shape[1]
	sigma2 = sse / (n - k)
	xtx_inv = np.linalg.inv(X.T.dot(X))
	var_coef = sigma2 * xtx_inv
	se_alpha = float(math.sqrt(var_coef[0, 0]))
	se_beta = float(math.sqrt(var_coef[1, 1]))
	t_alpha = alpha / se_alpha if se_alpha > 0 else float('nan')
	t_beta = beta / se_beta if se_beta > 0 else float('nan')

	return {
		'alpha': alpha,
		'beta': beta,
		'se_alpha': se_alpha,
		'se_beta': se_beta,
		't_alpha': t_alpha,
		't_beta': t_beta,
		'r2': r2,
		'n': n,
	}


def capm_expected_return(beta: float, market_premium: float, risk_free: float = 0.0) -> float:
	"""Compute expected return under CAPM: E[R] = Rf + beta * (E[Rm] - Rf).

	`market_premium` should be E[Rm] - Rf.
	"""
	return float(risk_free + beta * market_premium)


def _demo():
	"""Small self-contained demo that simulates data and prints estimation results."""
	np.random.seed(42)
	n = 252  # one year daily
	true_alpha = 0.0002
	true_beta = 1.2
	market_excess = np.random.normal(loc=0.0005, scale=0.01, size=n)
	noise = np.random.normal(scale=0.01, size=n)
	asset_excess = true_alpha + true_beta * market_excess + noise

	res = estimate_beta(asset_excess, market_excess)

	print("CAPM estimation demo")
	print(f"observations: {res['n']}")
	print(f"estimated alpha: {res['alpha']:.6f}  (se {res['se_alpha']:.6f}, t {res['t_alpha']:.2f})")
	print(f"estimated beta : {res['beta']:.4f}  (se {res['se_beta']:.4f}, t {res['t_beta']:.2f})")
	print(f"R-squared: {res['r2']:.4f}")

	# expected return example: suppose market premium is 6% annual -> daily ~0.06/252
	market_premium_daily = 0.06 / 252
	rf_daily = 0.01 / 252
	exp_daily = capm_expected_return(res['beta'], market_premium_daily, rf_daily)
	print(f"CAPM expected daily return (approx): {exp_daily:.6f}")


if __name__ == '__main__':
	_demo()

