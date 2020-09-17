function [kk, lags] = ccf(x ,y, m, w);
%CCF   compute cross-correlation function at a few lags
%---   in frequency domain via Ch.M. Rader's algorithm.
%
%      ccf =  SUM{ x[n+lag] y*[n] }  may be complex-valued
%
%   Usage:   [kk, lags] = ccf(x, y, m [,w]);
%
%     kk : cross-correlation function 
%   lags : index vector for cross-correlation values
%     x  : input signal 1
%     y  : input signal 2
%     m  : desired length of ccf ( = length of FFT used)
%     w  : if present, a Hann window is applied to ccf
%

%---------------------------------------------------------------
% copyright 1994, by C.S. Burrus, J.H. McClellan, A.V. Oppenheim,
% T.W. Parks, R.W. Schafer, & H.W. Schussler.  For use with the book
% "Computer-Based Exercises for Signal Processing Using MATLAB"
% (Prentice-Hall, 1994).
%---------------------------------------------------------------

if nargin<3 | nargin>4 | nargout~=2,
   error('Correct usage: [kk,la] = ccf(x,y,m [,w]);');
end;

x  = x(:).';   y  = y(:).';
m = m - rem(m,2);  %<-- make m even, because m = FFT length
m2 = m/2;
Lx = length(x);   Ly = length(y);   Lxy = min(Lx,Ly);
L = min(Lxy+m2, max(Lx,Ly));
if( Lx < L )
   x = [ x, zeros(1,L-Lx) ];
else
   x = x(1:L);   end
if( Ly < L )
   y = [ y, zeros(1,L-Ly) ];
else
   y = y(1:L);   end
mu = (-1).^(0:m-1);
ax = zeros(1,m);   ay = zeros(1,m);
zx = zeros(1,m);   zy = zeros(1,m);
n1 = 1;
while( n1 <= L )
   n2 = min( n1+m2-1, L );
   zix = fft(x(n1:n2), m);
   ziy = fft(y(n1:n2), m);
   ax  = ax + zix.*conj( ziy + mu.*zy );
   ay  = ay + conj(ziy).*( zix + mu.*zx );
   zx  = zix;
   zy  = ziy;
   n1 = n1 + m2;
end;
kx = ifft(ax)/Lxy;
ky = ifft(ay)/Lxy;
kk = [ ky(m2+1:m)  kx(1:m2+1) ];
if( ~any(imag([x,y])) ),
   kk = real(kk);  end
if nargin==4,
   kk = kk.*hanning(m+1)'; end;
lags = -m2:m2;
