const input = await Deno.readTextFile("./input.in");

class Queue<T> {
    _values: T[] = [];
    _head: number = 0;
    get length(): number {
        return this._values.length - this._head;
    }
    get empty(): boolean {
        return this.length <= 0;
    }
    get front(): T {
        return this._values[this._head];
    }
    push(val: T) {
        this._values.push(val);
    }
    pop(): T {
        this._head ++;
        return this._values[this._head - 1];
    }
}

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
                // 使用 (a ^ b) >>> 0 以保证结果为一个非负数, 如
                // 3298161905 ^ 4 = -996805387
                // (3298161905 ^ 4) >>> 0 = 3298161909
                this.registers[1] = (combo_operand ^ this.registers[1]) >>> 0;
                break;
            case 2:
                this.registers[1] = (value + 8) % 8;
                break;
            case 3:
                if (this.registers[0] === 0) break;
                this.pointer = combo_operand;
                return null;
            case 4:
                // 使用 (a ^ b) >>> 0 以保证结果为一个非负数, 如
                // 3298161905 ^ 4 = -996805387
                // (3298161905 ^ 4) >>> 0 = 3298161909
                this.registers[1] = (this.registers[2] ^ this.registers[1]) >>> 0;
                break;
            case 5:
                this.pointer += 2;
                return (value + 8) % 8;
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
const target = computer.program;
const Q = new Queue<number>();
Q.push(0);
while (!Q.empty) {
    const front = Q.pop();
    for (let i = front * 8; i < (front + 1) * 8; i ++) {
        computer.registers[0] = i;
        const outputs = computer.runProgram();
        if (outputs[0] === target[target.length - outputs.length])
            Q.push(i);
        if (outputs.toString() === target.toString()) {
            console.log(i);
            Deno.exit(0);
        }
    }
}
