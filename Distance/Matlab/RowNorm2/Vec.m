classdef Vec < handle
    
    properties
        dimension
        nrow
        alpha
        array
        result
    end
    
    methods
        % Constructor
        function obj = Vec(dimension, nsample1, nsample2)
            obj.dimension = dimension;
            obj.nrow = nsample1;
        end
        
        % Data initialization
        function init(obj, p1, p2, p3)
            obj.alpha = p1 .^ (0:obj.dimension-1);
            obj.array = (0:obj.nrow-1)' + p2 .* (0:obj.dimension-1);
        end
        
        % Kernel
        function run(obj)
            obj.result = sqrt(sum(obj.array.^2 .* obj.alpha, 2));
            % Summing along the rows seems faster than along the columns
            % even if Matlab is supposed to be column-major order...
        end
        
        % Checksum
        function c = checksum(obj)
            c = sum(obj.result);
        end
    end
    
end

