function [  ] = generate_loop( )
%GENERATE_LOOP Summary of this function goes here
%   Detailed explanation goes here
    theta1 = -2*pi:0.02:0;
    theta2 = 0.0:0.02: 2*pi;
    dsig = @(x) exp(x) ./ (1 + exp(x)).^2;    
    rho1 = 10;  
    rho2 = 10;
    lumps = randi([5, 40], 1);
    
    for i = 1:lumps
        size = 20 * rand() - 10;
        phase = rand() * 2 * pi - pi;
        rho1 = rho1 + size * dsig(10 * (theta1 + phase));
        rho2 = rho2 + size * dsig(10 * (theta2 + phase));
    end
    
%     size = 25;
%     phase = 0;
%     
%     rho1 = rho1 + size * dsig(10 * (theta1 + phase));
%     rho2 = rho2 + size * dsig(10 * (theta2 + phase));
    
    rho = 0:0.02:2*pi;
    for i = 1:315
        rho(i) = max(abs(1 - rho1(i)), abs(1 - rho2(i)));
    end
    
    polar(theta2, rho);
end

