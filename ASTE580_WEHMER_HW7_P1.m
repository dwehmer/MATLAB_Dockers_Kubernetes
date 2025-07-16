% Drew Wehmer
% ASTE 580
% HW 7
% Problem 1

function three_body_solver
    disp('PROBLEM 1')

    %% VARIABLES

    G = 1;
    m1 = 1;
    m2 = 2;
    m3 = 3;
    masses = [m1, m2, m3];

    %% INITIAL CONDITIONS (t0)

    r1 = [0; 0; 0];
    r2 = [1; 0; 0];
    r3 = [1/2; sqrt(3)/2; 0];

    v1 = [0; 0; 0];
    v2 = [0; sqrt(6); 0];
    v3 = [-3*sqrt(2)/2; sqrt(6)/2; 0];

    % State Vector
    y0 = [r1; v1; r2; v2; r3; v3];


    %% SOLVE ODE
    % time integral
    tspan = [0, pi];

    [T, Y] = ode45(@(t, y) three_body_solution(t, y, masses, G), tspan, y0);

    %% PLOT
    % time step to plot
    time_step = [0, pi/4, pi/2, 3*pi/4];

    figure; hold on; grid on;
    colors = {'r', 'b', 'c'};

    for i = 1:length(time_step)
        t_target = time_step(i);
        y_interp = interp1(T, Y, t_target);

        %extract positions
        r1 = y_interp(1:3);
        r2 = y_interp(7:9);
        r3 = y_interp(13:15);

        %Compute Center of Mass
        rcm = (m1*r1 + m2*r2 + m3*r3) / (m1 + m2 + m3);

        r1_rel = r1 - rcm;
        r2_rel = r2 - rcm;
        r3_rel = r3 - rcm;

        % Plot Triangle
        plot([r1_rel(1), r2_rel(1), r3_rel(1), r1_rel(1)], ...
             [r1_rel(2), r2_rel(2), r3_rel(2), r1_rel(2)], ...
             '-o', 'DisplayName', sprintf('t = %.2f', t_target));
    
        % Draw 3 concentric circles through each particle, centered at rcm
        radii = [norm(r1_rel(1:2)), norm(r2_rel(1:2)), norm(r3_rel(1:2))];
        for j = 1:3
            theta = linspace(0, 2*pi, 300);
            x_circ = radii(j) * cos(theta);
            y_circ = radii(j) * sin(theta);
            plot(x_circ, y_circ, 'Color', colors{j}, ...
                 'DisplayName', sprintf('Circle through r%d at t=%.2f', j, t_target));
        end
    end

    legend('0', 'pi/4', 'pi/2', '3pi/4');
    xlabel('x'); ylabel('y');
    title('Three-Body Positions in X-Y Plane Relative to Rcm');
    axis equal;
end



%% THREE BODY FUNCTION

function dydt = three_body_solution(~, y, masses, G)
    % initalize the masses
    m1 = masses(1);
    m2 = masses(2);
    m3 = masses(3);
    
    % intialize state vector
    r1 = y(1:3);
    v1 = y(4:6);
    r2 = y(7:9);
    v2 = y(10:12);
    r3 = y(13:15);
    v3 = y(16:18);
    
    % Compute distances
    r21 = r2 - r1;
    r31 = r3 - r1;
    r32 = r3 - r2;
    r12 = -r21;
    r13 = -r31;
    r23 = -r32;

    % Normalized distances
    r21n = norm(r21);
    r31n = norm(r31);
    r32n = norm(r32);
    r12n = r21n;
    r13n = r31n;
    r23n = r32n;

    % Acceleration portion
    a1 = G * (m2 * r21 / r21n^3 + m3 * r31 / r31n^3);
    a2 = G * (m1 * r12 / r12n^3 + m3 * r32 / r32n^3);
    a3 = G * (m1 * r13 / r13n^3 + m2 * r23 / r23n^3);

    % Combine
    dydt = [v1; a1; v2; a2; v3; a3];
end


    
    
