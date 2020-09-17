% Implementacion de un filtro desconocido:
function [y] = unknown_filter(x)

[b,a]=ellip(6,3,50,0.7);

% fvtool(b,a);
y = filter(b, a, x);