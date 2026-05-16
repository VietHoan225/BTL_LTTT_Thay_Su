#include<bits/stdc++.h>

using namespace std;

void generate_mcq(string question, string correct_ans, vector<string> wrong_suggestions) {
    set<string> unique_wrongs;
    for (auto &w : wrong_suggestions) {
        if (w != correct_ans && !w.empty()) {
            unique_wrongs.insert(w);
        }
    }
    
    int fallback_counter = 1;
    while (unique_wrongs.size() < 3) {
        unique_wrongs.insert(correct_ans + "_" + to_string(fallback_counter++));
    }

    vector<pair<string, bool>> final_options;
    final_options.push_back({correct_ans, true});
    auto it = unique_wrongs.begin();
    for (int i = 0; i < 3; i++) {
        final_options.push_back({*it, false});
        it++;
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(final_options.begin(), final_options.end(), default_random_engine(seed));

    cout << "===MCQ_START===\n";
    cout << question << "\n";
    char correct_label = 'A';
    for (int i = 0; i < 4; i++) {
        cout << char('A' + i) << ". " << final_options[i].first << "\n";
        if (final_options[i].second == true) {
            correct_label = char('A' + i);
        }
    }
    cout << "Đáp án đúng: " << correct_label << "\n";
    cout << "===MCQ_END===\n\n";
}

// ==========================================
// TYPE 1: ARITHMETIC CODING
// ==========================================
void solve_arithmetic(int mode) {
    string s; cin >> s;
    map<char, int> freq;
    for (char c : s) freq[c]++;
    
    map<char, pair<long double, long double>> prob_range;
    long double current_low = 0.0;
    
    if (mode == 1) {
        cout << "========================================================\n";
        cout << "        --- LỜI GIẢI CHI TIẾT: MÃ HÓA SỐ HỌC ---\n";
        cout << "========================================================\n";
        cout << "[BƯỚC 1] BẢNG PHÂN BỐ XÁC SUẤT TRÊN CHUỖI DÀI " << s.length() << ":\n";
        cout << "--------------------------------------------------------\n";
        cout << "  Ký tự | Tần suất |  Xác suất  | Khoảng phân bổ [Low, High)\n";
        cout << "--------------------------------------------------------\n";
    }
    
    for (auto const& [c, count] : freq) {
        long double p = (long double)count / s.length();
        prob_range[c] = {current_low, current_low + p};
        if (mode == 1) {
            cout << "    '" << c << "'   | " << setw(8) << count << " | " 
                 << fixed << setprecision(4) << p << "   | [" << current_low << ", " << current_low + p << ")\n";
        }
        current_low += p;
    }
    
    long double low = 0.0, high = 1.0;
    long double mid_low = 0, mid_high = 0;
    int target_m = max(1, (int)s.length() / 2);

    if (mode == 1) {
        cout << "--------------------------------------------------------\n\n";
        cout << "[BƯỚC 2] TIẾN TRÌNH MÃ HÓA TỪNG KÝ TỰ:\n";
        cout << "--------------------------------------------------------\n";
    }
    
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        long double range = high - low;
        high = low + range * prob_range[c].second;
        low = low + range * prob_range[c].first;
        if (mode == 1) {
            cout << "  Đọc '" << c << "' -> Khoảng hiện tại: [" << fixed << setprecision(8) << low << ", " << high << ")\n";
        }
        if (i == target_m - 1) {
            mid_low = low; mid_high = high;
        }
    }
    
    long double encoded_val = (low + high) / 2.0;
    int k = ceil(-log2(high - low)) + 1;
    string binary_code = "";
    long double temp = encoded_val;
    for (int i = 0; i < k; i++) {
        temp *= 2.0;
        if (temp >= 1.0) { binary_code += "1"; temp -= 1.0; } 
        else { binary_code += "0"; }
    }

    if (mode == 1) {
        cout << "--------------------------------------------------------\n\n";
        cout << "[BƯỚC 3] KẾT QUẢ MÃ HÓA CHUNG CỦA CHUỖI:\n";
        cout << "  * Giá trị phân số thập phân chọn mã: " << fixed << setprecision(8) << encoded_val << "\n";
        cout << "  * Số bit tối thiểu cần sinh ra (k) : " << k << " bit\n";
        cout << "  * Chuỗi mã hóa nhị phân thu được    : " << binary_code << "\n";
        cout << "========================================================\n";
    } else if (mode == 0) {
        cout << "[STANDARD OUTPUT - ARITHMETIC]\n";
        cout << "Value  : " << fixed << setprecision(8) << encoded_val << "\n";
        cout << "Binary : " << binary_code << "\n";
        cout << "Length : " << k << " bits\n";
    } else if (mode == 2) {
        string w1 = binary_code + "0";
        string w2 = binary_code; if(!w2.empty()) w2.back() = (w2.back() == '1' ? '0' : '1');
        string w3 = binary_code; if(!w3.empty()) w3[0] = (w3[0] == '1' ? '0' : '1');
        generate_mcq("Đâu là mã nhị phân hợp lệ của chuỗi '" + s + "'?", binary_code, {w1, w2, w3});

        int target_bit = max(1, k / 2);
        string correct_bit = string(1, binary_code[target_bit - 1]);
        generate_mcq("Sau khi mã hóa số học chuỗi '" + s + "', bit thứ " + to_string(target_bit) + " (tính từ 1) trong chuỗi nhị phân kết quả là gì?", correct_bit, {correct_bit == "0" ? "1" : "0", "Không xác định được", "Trình biên dịch báo lỗi"});

        generate_mcq("Cần tối thiểu bao nhiêu bit nhị phân để mã hóa chính xác khoảng giá trị sau khi nén chuỗi '" + s + "'?", to_string(k) + " bit", {to_string(k+1)+" bit", to_string(k-1)+" bit", to_string(k+3)+" bit"});

        stringstream ss_true, ss_f1, ss_f2, ss_f3;
        ss_true << fixed << setprecision(5) << "[" << mid_low << ", " << mid_high << ")";
        ss_f1 << fixed << setprecision(5) << "[" << mid_low + 0.001 << ", " << mid_high + 0.001 << ")";
        ss_f2 << fixed << setprecision(5) << "[" << mid_low << ", " << mid_high + 0.005 << ")";
        ss_f3 << fixed << setprecision(5) << "[" << mid_low - 0.002 << ", " << mid_high << ")";
        generate_mcq("Sau khi đọc đến ký tự thứ " + to_string(target_m) + " của chuỗi '" + s + "', khoảng giá trị [Low, High) mới được cập nhật là bao nhiêu?", ss_true.str(), {ss_f1.str(), ss_f2.str(), ss_f3.str()});
    }
}

// ==========================================
// TYPE 2: LZW CODING
// ==========================================
void solve_lzw(int mode) {
    string s; cin >> s;
    unordered_map<string, int> dict;
    vector<string> reverse_dict(4096);
    for (int i = 0; i < 256; i++) {
        dict[string(1, char(i))] = i;
        reverse_dict[i] = string(1, char(i));
    }
    
    string p = ""; p += s[0];
    int code = 256;
    vector<int> output_code;
    vector<pair<int, string>> history_dict;
    
    if (mode == 1) {
        cout << "========================================================\n";
        cout << "         --- LỜI GIẢI CHI TIẾT: MÃ HÓA LZW ---\n";
        cout << "========================================================\n";
        cout << "[BƯỚC TIẾN TRÌNH NÉN CHUỖI TRỰC TIẾP]:\n";
        cout << "--------------------------------------------------------\n";
        cout << "   Xâu hiện tại (P) | Kí tự tiếp (C) | Output | Thêm Từ Điển (Mã)\n";
        cout << "--------------------------------------------------------\n";
    }
    
    for (int i = 0; i < s.length(); i++) {
        string c = (i != s.length() - 1) ? string(1, s[i + 1]) : "";
        if (dict.find(p + c) != dict.end()) {
            p = p + c;
        } else {
            if (mode == 1) {
                cout << "   " << setw(16) << p << " | " << setw(14) << (c.empty() ? "EOF" : c) 
                     << " | " << setw(6) << dict[p] << " | " << p+c << " (" << code << ")\n";
            }
            output_code.push_back(dict[p]);
            dict[p + c] = code;
            reverse_dict[code] = p + c;
            history_dict.push_back({code, p + c});
            code++; p = c;
        }
    }
    output_code.push_back(dict[p]);
    if (mode == 1) {
        cout << "   " << setw(16) << p << " | " << setw(14) << "EOF" 
             << " | " << setw(6) << dict[p] << " | [Kết thúc nén]\n";
        cout << "--------------------------------------------------------\n";
        cout << "=> Dãy mã hóa LZW đầu ra: ";
        for (int x : output_code) cout << x << " ";
        cout << "\n========================================================\n";
    } else if (mode == 0) {
        cout << "[STANDARD OUTPUT - LZW]\n";
        cout << "Tokens count : " << output_code.size() << "\n";
        cout << "Stream       : ";
        for (int x : output_code) cout << x << " ";
        cout << "\n";
    } else if (mode == 2) {
        int ans = output_code.size();
        generate_mcq("Số lượng từ mã sinh ra sau khi nén LZW chuỗi '" + s + "' là bao nhiêu?", to_string(ans), {to_string(ans+1), to_string(ans-1 > 0 ? ans-1 : ans+2), to_string(ans+3)});

        if (!history_dict.empty()) {
            int target_idx = history_dict.size() / 2;
            int ask_code = history_dict[target_idx].first;
            string ask_str = history_dict[target_idx].second;
            string w1 = ask_str; reverse(w1.begin(), w1.end()); if(w1 == ask_str) w1 += "_X";
            generate_mcq("Trong quá trình nén LZW chuỗi '" + s + "', cụm ký tự nào sẽ được thêm vào từ điển với mã số " + to_string(ask_code) + "?", ask_str, {w1, ask_str + "A", "Chưa thêm ký tự nào"});
        }

        if (output_code.size() >= 2) {
            int ask_k = min(3, (int)output_code.size());
            int correct_val = output_code[ask_k - 1];
            generate_mcq("Giá trị mã hóa (Output) thứ " + to_string(ask_k) + " được xuất ra trong quá trình nén LZW chuỗi '" + s + "' là bao nhiêu?", to_string(correct_val), {to_string(correct_val+1), to_string(correct_val-5), to_string(output_code[0] + 12)});
        }
    }
}

// ==========================================
// TYPE 3: HAMMING DISTANCE
// ==========================================
void solve_hamming(int mode) {
    int n; cin >> n;
    vector<string> codes(n);
    for (int i = 0; i < n; i++) cin >> codes[i];
    
    int d_min = 1e9; string pair1, pair2;
    if (mode == 1) {
        cout << "========================================================\n";
        cout << "     --- LỜI GIẢI CHI TIẾT: KIỂM TRA BỘ MÃ LỖI ---\n";
        cout << "========================================================\n";
        cout << "[BƯỚC 1] QUÁ TRÌNH TÍNH TOÁN KHOẢNG CÁCH TOÀN BỘ CẶP MÃ:\n";
        cout << "--------------------------------------------------------\n";
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = 0;
            for (int k = 0; k < codes[i].length(); k++) {
                if (codes[i][k] != codes[j][k]) dist++;
            }
            if (mode == 1) {
                cout << "  -> Kiểm tra d(" << codes[i] << ", " << codes[j] << ") = " << dist << " bit lệch.\n";
            }
            if (dist < d_min) { d_min = dist; pair1 = codes[i]; pair2 = codes[j]; }
        }
    }
    
    int detect = d_min - 1;
    int correct = (d_min - 1) / 2;
    
    if (mode == 1) {
        cout << "--------------------------------------------------------\n\n";
        cout << "[BƯỚC 2] KẾT LUẬN NĂNG LỰC SỬA LỖI THEO CÔNG THỨC:\n";
        cout << "  * Khoảng cách mã nhỏ nhất (d_min)  = " << d_min << " (Giữa " << pair1 << " và " << pair2 << ")\n";
        cout << "  * Năng lực phát hiện lỗi bit (e)   = d_min - 1 = " << detect << " bit.\n";
        cout << "  * Năng lực sửa sai tối đa bit (t)  = floor((d_min - 1) / 2) = " << correct << " bit.\n";
        cout << "========================================================\n";
    } else if (mode == 0) {
        cout << "[STANDARD OUTPUT - HAMMING CAPACITY]\n";
        cout << "d_min             : " << d_min << "\n";
        cout << "Error Detection(e): " << detect << " bits\n";
        cout << "Error Correction(t): " << correct << " bits\n";
    } else if (mode == 2) {
        generate_mcq("Khả năng sửa lỗi tối đa (t) của bộ mã đầu vào là bao nhiêu bit?", to_string(correct) + " bit", {to_string(correct + 1) + " bit", to_string(detect) + " bit", to_string(d_min) + " bit"});

        generate_mcq("Bộ mã nguồn đã cho có khả năng phát hiện tối đa bao nhiêu lỗi bit (e)?", to_string(detect) + " bit", {to_string(correct) + " bit", to_string(d_min) + " bit", to_string(detect + 1) + " bit"});

        string wrong_p1 = codes[0] + " và " + codes[n-1];
        string wrong_p2 = "Không có cặp nào";
        if(wrong_p1 == pair1 + " và " + pair2) wrong_p1 = codes[0] + " và " + (n > 2 ? codes[1] : "bộ mã rỗng");
        generate_mcq("Cặp từ mã nào trong bộ mã có khoảng cách Hamming nhỏ nhất (d_min)?", pair1 + " và " + pair2, {wrong_p1, wrong_p2, "Tất cả các cặp đều có d bằng nhau"});
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            int type, mode; cin >> type >> mode;
            if (type == 1) solve_arithmetic(mode);
            else if (type == 2) solve_lzw(mode);
            else if (type == 3) solve_hamming(mode);
        }
    }
    return 0;
}