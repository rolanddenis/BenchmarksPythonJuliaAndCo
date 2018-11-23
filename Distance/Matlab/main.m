function main(problem, method, dimension, nsample1, nsample2)
    % Command-line parameters
    dimension = str2double(dimension);
    nsample1  = str2double(nsample1);
    nsample2  = str2double(nsample2);
    
    % Config
    p1 = 1.1;
    p2 = 1.2;
    p3 = 1.3;
    warming_time = 1;
    run_time = 10;
    min_run = 3;
    
    % Kernel initialization
    old_path = addpath(problem);
    cstr = str2func(method);
    kernel = cstr(dimension, nsample1, nsample2);
    kernel.init(p1, p2, p3);
    
    % Runs
    nrun = 0;
    is_warming = true;
    tic();
    
    while true
        kernel.run();
        
        total_duration = toc();
        
        % Managing warming and run time
        if is_warming && total_duration >= warming_time
            is_warming = false;
            tic();
        elseif ~is_warming
            nrun = nrun + 1;
            
            % Ending benchmark
            if total_duration >= run_time && nrun >= min_run
                break;
            end
        end
    end
    
    % Checksum
    checksum = kernel.checksum();
    
    % Mean duration
    mean_duration = total_duration / nrun;
    
    % Displaying result
    fprintf('%d %f\n', mean_duration, checksum);

    path(old_path);
end