classdef Loop < handle
    
    properties
        dimension
        nrow
        alpha
        array
        result
    end
    
    methods
        % Constructor
        function obj = Loop(dimension, nsample1, nsample2)
            obj.dimension = dimension;
            obj.nrow = nsample1;
        end
        
        % Data initialization
        function init(obj, p1, p2, p3)
            obj.alpha = p1 .^ (0:obj.dimension-1);
            obj.array = (0:obj.nrow-1)' + p2 .* (0:obj.dimension-1);
            obj.result = zeros(obj.nrow, 1);
        end
        
        % Kernel
        function run(obj)
            for i = 1:obj.nrow
                row_sum = 0;
                for d = 1:obj.dimension
                    row_sum = row_sum + obj.array(i,d)^2 * obj.alpha(d);
                end
                obj.result(i) = sqrt(row_sum);
            end
        end
        
        % Checksum
        function c = checksum(obj)
            c = sum(obj.result);
        end
    end
    
end

