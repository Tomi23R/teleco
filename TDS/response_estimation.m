clear all
close all

aux = [1 zeros(1, 999)];
ruido = randn(1, 10000);

ri = unknown_filter(aux);
maximo_ri = max(ri);

for i = 1:length(ri)   
    if ri(i) > 0.01*maximo_ri        
        transi = i+1;
    end    
end

salida_ruido = unknown_filter(ruido);

[kk, lags] = ccf(salida_ruido(transi:end), ruido(transi:end), 128);

figure;
stem(lags, kk); % Correlacion cruzada

hold on;
plot([-64:64], [zeros(1,64) ri(1:65)],'r');
legend('Correlacion Cruzada', 'Respuesta al impulso');