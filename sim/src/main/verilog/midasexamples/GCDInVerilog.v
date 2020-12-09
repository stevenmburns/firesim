module GCDInVerilog(
  input         master_clk,
  input  [15:0] a,
  input  [15:0] b,
  input         e,
  output [15:0] z,
  output        v
);

   reg [15:0] 	x;
   reg [15:0] 	y;

   assign z = x;
   assign v = y == 16'b0;

  wire x_gt_y = x > y;
  wire [15:0] xminusy = x - y;
  wire x_le_y = ~x_gt_y;
  wire [15:0] yminusx = y - x;

  always @(posedge master_clk) begin
    if (e) begin
      x <= a;
    end else if (x_gt_y) begin
       x <= xminusy;
    end

    if (e) begin
      y <= b;
    end else if (x_le_y) begin
      y <= yminusx;
    end
  end
endmodule