library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.ALL;

entity ExecutionUnit is
    Port ( nextPC : in STD_LOGIC_VECTOR(15 downto 0);
           rd1 : in STD_LOGIC_VECTOR(15 downto 0);
           rd2 : in STD_LOGIC_VECTOR(15 downto 0);
           imm : in STD_LOGIC_VECTOR(15 downto 0);
           func : in STD_LOGIC_VECTOR(2 downto 0);
           sa : in STD_LOGIC;
           aluSrc : in STD_LOGIC;
           aluOps : in STD_LOGIC_VECTOR(2 downto 0);
           branch : out STD_LOGIC_VECTOR(15 downto 0);
           aluOut : out STD_LOGIC_VECTOR(15 downto 0);
           zFlag : out STD_LOGIC);
end ExecutionUnit;

architecture Behavioral of ExecutionUnit is
   
signal ctrl : STD_LOGIC_VECTOR(2 downto 0);
signal dataIN : STD_LOGIC_VECTOR(15 downto 0);
signal aluOutput : STD_LOGIC_VECTOR(15 downto 0);

begin
     aluOut <= aluOutput;
    branch <= nextPC + imm;

    process(aluSrc)
    begin
        if aluSrc = '1' then 
           dataIN<=imm;
           else
           dataIN<=rd2;
           end if;
    end process;
			  
    process(aluOps, func)
    begin
        case aluOps is
            when "000" => ctrl <= func; --R type
            when "001" => ctrl <= "000"; -- +
            when "010" => ctrl <= "001"; -- -
            when "101" => ctrl <= "001"; --   should be -
            when "110" => ctrl <= "111"; --   should be slt
            when others => ctrl <= "000"; 
        end case;
    end process;


    process(ctrl, rd1, rd2, dataIN, sa, aluOutput)
    begin
        case ctrl  is
            when "000" => --  addition operation
                aluOutput <= rd1 + dataIN;

            when "001" =>  -- substraction operation
            aluOutput <= rd1 - dataIN;   

            when "010" => -- shift left logic

                 if sa = '1' then
                    aluOutput <= dataIN(14 downto 0) & "0";
                    else 
                    aluOutput <= dataIN;
                    end if;

            when "011" => -- shift right logic
             
                if sa = '1' then 
                aluOutput <= "0" & dataIN(15 downto 1);
                else 
                aluOutput <= dataIN;
                end if;

            when "100" => -- adn operation
            aluOutput<=rd1 and dataIN;	

            when "101" => -- or operation
            aluOutput<=rd1 or dataIN; 

            when "110" => -- exclusive or operation
            aluOutput<=rd1 xor dataIN;	

            when "111" => -- set on lower than 
                if rd1 < dataIN then
                    aluOutput <= X"0001";
                else 
                aluOutput <= X"0000";
                end if;
            when others =>  aluOutput <= X"0000";              
        end case;

       
    end process;

    process(aluOutput)
    begin
        if aluOutput = x"0000" then 
        zFlag <= '1';
        else
       zFlag <= '0';
       end if;   
       end process;

end Behavioral;