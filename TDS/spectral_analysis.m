function [spec] = spectral_analysis(x, fs, N, L, window, R)

% VENTANAS:
if strcmp(window, 'rectangular')
    wind = rectwin(L);
elseif strcmp(window, 'hamming')
    wind = hamming(L);
elseif strcmp(window, 'hanning')
    wind = hanning(L);
elseif strcmp(window, 'bartlett')
    wind = bartlett(L);
elseif strcmp(window, 'blackman')
    wind = blackman(L);
end


puntos_reales_nfft = ceil((1+N)/2);

saltos = ceil((length(x)-L)/R);

spec_aux = zeros(puntos_reales_nfft, saltos);



for i = 0:(saltos-1)    
    x_vent = x((1+i*R):(L+i*R))' .* wind;    
    x_vent_fft = fft(x_vent, N);    
    spec_aux(:, 1+i) = x_vent_fft(1:puntos_reales_nfft);
end

frecuencias = (0:puntos_reales_nfft-1)*fs/N;
tiempo = ((L/2):R:L/2+(saltos-1)*R) / fs;


spec = 20*log10(spec_aux);

figure;

imagesc(tiempo, frecuencias, real(spec));
colormap('gray');

xlabel('Tiempo (s)');
ylabel('Frecuencia (Hz)');
colorbar

shading interp;
axis tight;
view(0, 90);
