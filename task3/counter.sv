module counter #(
    parameter WIDTH = 8
)(
    input logic clk,
    input logic rst,
    input logic load_en,
    input logic [WIDTH-1:0] din,
    output logic [WIDTH-1:0] count
);

always_ff @(posedge clk) begin
    if (rst) 
        count <= {WIDTH{1'b0}};
    else if (load_en) 
        count <= din;
    else
        count <= count + {{WIDTH-1{1'b0}}, 1};
end

endmodule
