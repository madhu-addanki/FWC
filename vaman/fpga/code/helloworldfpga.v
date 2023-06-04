module helloworldfpga(

    input  wire A,
    input  wire Q,
    
    output wire F,
    );
   
    
    always @(*)
    begin
    F=(!(A&Q)); 
    end
    endmodule
