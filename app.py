from flask import Flask, request, jsonify, render_template
import subprocess
import platform
import os

app = Flask(__name__)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

if platform.system() == "Windows":
    BINARY_PATH = os.path.join(BASE_DIR, "main.exe")
else:
    BINARY_PATH = os.path.join(BASE_DIR, "main")

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/run', methods=['POST'])
def run_algo():
    data = request.json
    algo_type = int(data.get('type'))
    mode = int(data.get('mode'))
    
    # Định dạng chuẩn ICPC: T = 1 -> TYPE -> MODE
    input_data = f"1\n{algo_type} {mode}\n"
    
    if algo_type in [1, 2]:
        input_data += f"{data.get('input_string')}\n"
    elif algo_type == 3:
        codes = data.get('input_codes', [])
        input_data += f"{len(codes)}\n"
        for code in codes:
            input_data += f"{code}\n"

    try:
        process = subprocess.Popen(
            ['./main'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        stdout, stderr = process.communicate(input=input_data)
        
        if process.returncode != 0:
            return jsonify({'success': False, 'output': f"Lỗi C++: {stderr}"})
            
        return jsonify({'success': True, 'output': stdout})
        
    except Exception as e:
        return jsonify({'success': False, 'output': f"Lỗi hệ thống: {str(e)}"})

if __name__ == '__main__':
    app.run(debug=True, port=5000)