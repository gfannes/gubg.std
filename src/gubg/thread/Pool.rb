module Gubg
    module Thread
        class Pool
            def initialize(j: nil)
            end

            def close()
            end

            def self.open(j: nil)
                tp = Pool.new(j: j)
                yield(tp)
                tp.close()
            end

            def add_job()
            end
        end
    end
end