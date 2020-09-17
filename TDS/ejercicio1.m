close all
clear all

window = 'blackman';
N = 1024;
fs = 8000;

L = 0.02*fs; R = 0.5*L;


n = 0:(1/fs):(1-(1/fs));

senal = [cos(2*pi*1000*n) cos(2*pi*2000*n)];
% senal = [cos(2*pi*1000*n) cos(2*pi*2000*n) cos(2*pi*3000*n)];

% % [audio, fs_audio] = audioread('aaaaaaa.ogg');
% % audio(11840:42100) = zeros(1, 30261); % Con esto eliminamos el ruido del inicio

% % figure, plot(audio);
% % xlabel('Muestras');

[spec] = spectral_analysis(senal, fs, N, L, window, R);
% [spec] = spectral_analysis(audio, fs_audio, N, L, window, R);

% tiempos = [0:(1/fs):(2-(1/fs))];
% figure, plot(tiempos, senal);