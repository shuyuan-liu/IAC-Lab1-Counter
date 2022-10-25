module counter #(
    parameter WIDTH = 8
)(
    input logic clk,
    input logic rst,
    input logic dir,
    output logic [WIDTH-1:0] count
);

always_ff @(posedge clk) begin
    if (rst) 
        count <= {WIDTH{1'b0}};
    else if (dir)
        count <= count + {{WIDTH-1{1'b0}}, 1};
    else
        count <= count - {{WIDTH-1{1'b0}}, 1};
end

endmodule
