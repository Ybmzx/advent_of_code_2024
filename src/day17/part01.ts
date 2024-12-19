const input = await Deno.readTextFile("./input.in");

class Computer {
    registers: [number, number, number] = [0, 0, 0];
    program: number[] = new Array<number>();
    pointer: number = 0;
    constructor(input: string) {
        const lines = input.split(/\r?\n/);
        for (let i = 0; i < 3; i ++) {
            this.registers[i] = parseInt(lines[i].split(':')[1]);
        }
        this.program = lines[lines.length - 1].split(':')[1].split(',').map(x => parseInt(x));
    }

    get_combo_operand(combo_operand: number): number {
        if (combo_operand <= 3) return combo_operand;
        return this.registers[combo_operand - 4];
    }

    execCommand(instruction: number, combo_operand: number): number | null {
        const value = this.get_combo_operand(combo_operand);
        switch(instruction) {
            case 0:
                this.registers[0] = Math.floor(this.registers[0] / (2 ** value));
                break;
            case 1:
                this.registers[1] ^= combo_operand;
                break;
            case 2:
                this.registers[1] = value % 8;
                break;
            case 3:
                if (this.registers[0] === 0) break;
                this.pointer = combo_operand;
                return null;
            case 4:
                this.registers[1] ^= this.registers[2];
                break;
            case 5:
                this.pointer += 2;
                return value % 8;
            case 6:
                this.registers[1] = Math.floor(this.registers[0] / (2 ** value));
                break;
            case 7:
                this.registers[2] = Math.floor(this.registers[0] / (2 ** value));
                break;
        }
        this.pointer += 2;
        return null;
    }

    runProgram(): number[] {
        const outputs = new Array<number>();
        this.pointer = 0;
        while (this.pointer < this.program.length - 1) {
            const output = this.execCommand(this.program[this.pointer], this.program[this.pointer + 1]);
            if (output !== null) outputs.push(output);
        }
        return outputs;
    }
}

const computer = new Computer(input);
const outputs = computer.runProgram();
console.log(outputs.join(','));
