import pandas as pd
from collections import defaultdict
import sort
import sys
import os

def get_input_file():
    """获取输入文件路径"""
    data_xlsx = input("请输入表格文件地址 (直接回车使用默认地址 './data.xlsx'): ")
    if not data_xlsx.strip():
        data_xlsx = './data.xlsx'
        print(f"使用默认文件地址: {data_xlsx}")
    else:
        print(f"使用用户提供的文件地址: {data_xlsx}")

    # 检查文件是否存在
    if not os.path.exists(data_xlsx):
        print(f"错误: 文件 '{data_xlsx}' 不存在，请检查路径后重试。")
        sys.exit(1)
        
    return data_xlsx


def load_data(file_path):
    """从Excel文件加载数据"""
    df = pd.read_excel(file_path)
    total_rows = len(df)
    
    print("\n" + "-" * 8 + f"原始数据 (总行数: {total_rows})" + "-" * 8)
    print(df)
    print("\n")
    
    return df, total_rows


def validate_columns(df):
    """验证必要的列是否存在"""
    base_columns = ['序号', '标记名', '依赖']
    for col in base_columns:
        if col not in df.columns:
            print(f"错误：缺少必要的列 '{col}'")
            sys.exit(1)
    return base_columns


def identify_weight_columns(df, base_columns):
    """识别权重列"""
    all_columns = list(df.columns)
    weight_columns = []
    weight_indices = []
    
    # 显示所有列和索引
    print("表格中的所有列:")
    for i, col in enumerate(all_columns):
        is_base = "（基本列）" if col in base_columns else ""
        print(f"  列{i}: {col} {is_base}")
    
    # 找出可能的权重列
    for i, col in enumerate(all_columns):
        # 跳过基础列
        if col in base_columns:
            continue
        
        # 检查列是否包含数值数据
        if pd.api.types.is_numeric_dtype(df[col]) or df[col].apply(lambda x: isinstance(x, (int, float))).all():
            weight_columns.append(col)
            weight_indices.append(i)
    
    print(f"\n检测到的可能权重列: {weight_columns}")
    print(f"对应的列索引: {weight_indices}")
    
    return all_columns, weight_columns, weight_indices


def generate_formula_examples(all_columns, weight_indices):
    """生成权重计算公式示例"""
    print("\n自定义权重计算公式")
    print("注意: 在公式中使用列索引 C0, C1, C2...")
    print("示例: ")
    
    # 生成列索引映射
    column_index_map = {}
    for i, col in enumerate(all_columns):
        column_index_map[f"C{i}"] = col
    
    # 显示权重列的映射
    print("权重列映射:")
    for i in weight_indices:
        print(f"  C{i} = {all_columns[i]}")
    
    # 生成线性加权示例
    weights_example = [round(1/(i+1), 2) for i in range(len(weight_indices))]
    weights_sum = sum(weights_example)
    normalized_weights = [round(w/weights_sum, 2) for w in weights_example]
    linear_example = " + ".join([f"C{i}*{w}" for i, w in zip(weight_indices, normalized_weights)])
    print(f"- 线性加权: {linear_example}")
    
    # 生成非线性加权示例
    if len(weight_indices) >= 2:
        nonlinear_example = f"C{weight_indices[0]}**2 + C{weight_indices[1]}**0.5"
        if len(weight_indices) > 2:
            nonlinear_example += f" + log10(C{weight_indices[2]}+1)"
        print(f"- 非线性关系: {nonlinear_example}")
    
    # 生成复杂公式示例
    if len(weight_indices) >= 2:
        complex_example = f"max(C{weight_indices[0]}, C{weight_indices[1]})"
        if len(weight_indices) > 2:
            complex_example += f" * log10(C{weight_indices[2]}+1)"
        print(f"- 复杂公式: {complex_example}")
    
    # 生成默认公式
    default_formula = " + ".join([f"C{i}*{1.0/len(weight_indices):.2f}" for i in weight_indices])
    print(f"默认公式: {default_formula}")
    
    return default_formula


def get_user_formula(default_formula):
    """获取用户输入的公式"""
    try:
        print("提示：公式将用来计算得分，得分高的在前面")
        user_formula = input("请输入自定义权重计算公式 (直接回车使用默认公式): ")
        if not user_formula.strip():
            user_formula = default_formula
            print(f"使用默认公式: {user_formula}")
    except EOFError:
        user_formula = default_formula
        print(f"无法接受输入，使用默认公式: {user_formula}")
    
    return user_formula


def build_dependency_graph(df, all_columns, weight_indices):
    """构建依赖关系图"""
    print("\n" + "-" * 8 + "日志" + "-" * 8)
    
    graph = defaultdict(list)
    in_degree = defaultdict(int)
    tasks = {}
    processed_rows = 0
    
    for _, row in df.iterrows():
        processed_rows += 1
        
        task_id = row['序号']
        task_name = row['标记名']
        dependency_str = row['依赖']
        
        task_info = extract_task_info(row, all_columns)
        
        print(f"处理第{processed_rows}行: 任务ID={task_id}, 名称={task_name}, 依赖={dependency_str}")
        for i in weight_indices:
            col = all_columns[i]
            print(f"  C{i}({col})={row[col]}")
        
        # 保存任务信息
        tasks[task_id] = task_info
        
        # 处理依赖关系
        process_dependencies(dependency_str, task_id, graph, in_degree)
    
    print(f"> 处理了 {processed_rows}/{len(df)} 行数据")
    print(f"> 构建的任务字典包含 {len(tasks)} 个任务")
    print(f"> 依赖关系图中有 {len(graph)} 个有出边的节点")
    print(f"> 入度表中有 {len(in_degree)} 个节点")
    
    return graph, in_degree, tasks


def extract_task_info(row, all_columns):
    """从行数据中提取任务信息"""
    task_info = {'name': row['标记名']}
    
    # 添加所有列值到任务信息中
    for i, col in enumerate(all_columns):
        try:
            # 尝试将值转换为浮点数
            task_info[f"C{i}"] = float(row[col])
        except (ValueError, TypeError):
            # 如果不能转换为数字，则存储原始值
            task_info[f"C{i}"] = row[col]
    
    return task_info


def process_dependencies(dependency_str, task_id, graph, in_degree):
    """处理任务的依赖关系"""
    # 确保所有节点都在in_degree中
    if task_id not in in_degree:
        in_degree[task_id] = 0
        
    if pd.isna(dependency_str):
        return
    
    # 将依赖字符串分割为列表
    dependencies = str(dependency_str).split(',')
    
    for dep in dependencies:
        try:
            # 尝试转换为整数或保持原样
            dep = dep.strip()
            if dep.isdigit():
                dep = int(dep)
            
            graph[dep].append(task_id)
            in_degree[task_id] += 1
            print(f"  添加依赖: {dep} -> {task_id}")
        except Exception as e:
            print(f"  警告: 处理依赖 '{dep}' 时出错: {e}")


def perform_topological_sort(graph, in_degree, tasks, user_formula, all_columns, weight_indices):
    """执行拓扑排序并显示结果"""
    try:
        # 使用排序模块执行拓扑排序
        sorted_tasks = sort.topological_sort_with_weights(graph, in_degree, tasks, user_formula)
        
        display_task_scores(sorted_tasks, tasks, user_formula, all_columns, weight_indices)
        display_results(sorted_tasks, tasks)
        analyze_unprocessed_tasks(sorted_tasks, tasks, graph)
        
        return sorted_tasks
    except Exception as e:
        print(f"\n错误: 在执行排序时发生异常: {e}")
        return []


def display_task_scores(sorted_tasks, tasks, formula, all_columns, weight_indices):
    """显示任务得分"""
    print("\n" + "-" * 8 + "得分" + "-" * 8)
    for task_id in sorted_tasks:
        # 计算综合得分
        score = sort.calculate_priority_score(tasks[task_id], formula)
        print(f"{task_id}({tasks[task_id]['name']}) - 得分：{score:.2f}")
        
        # 显示各权重值
        weight_values = []
        for i in weight_indices:
            col_name = all_columns[i]
            col_index = f"C{i}"
            value = tasks[task_id].get(col_index, "N/A")
            weight_values.append(f"{col_index}({col_name})={value}")
        print(f"  权重值: {', '.join(weight_values)}")
    
    print("\n")


def display_results(sorted_tasks, tasks):
    """显示排序结果"""
    print("-" * 8 + "结果" + "-" * 8)
    print(f"排序后的任务数量: {len(sorted_tasks)}/{len(tasks)}")
    print("执行顺序:", end=" ")
    for task_id in sorted_tasks:
        print(f"{task_id}({tasks[task_id]['name']})", end=" → ")
    print("END")


def analyze_unprocessed_tasks(sorted_tasks, tasks, graph):
    """分析未处理的任务"""
    analysis = sort.analyze_unprocessed_tasks(sorted_tasks, tasks, graph)
    if analysis["unprocessed_count"] > 0:
        print(f"\n警告: 有 {analysis['unprocessed_count']} 个任务未被排序: {analysis['unprocessed_tasks']}")
        
        if analysis["cycles"]:
            print(f"循环依赖: {analysis['cycles']}")
        
        if analysis["isolated"]:
            print(f"孤立节点: {analysis['isolated']}")


def main():
    """主函数"""
    # 获取输入文件路径
    file_path = get_input_file()
    
    # 加载数据
    df, _ = load_data(file_path)
    
    # 验证必要的列
    base_columns = validate_columns(df)
    
    # 识别权重列
    all_columns, _, weight_indices = identify_weight_columns(df, base_columns)
    
    # 生成公式示例
    default_formula = generate_formula_examples(all_columns, weight_indices)
    
    # 获取用户的公式
    user_formula = get_user_formula(default_formula)
    
    # 构建依赖关系图
    graph, in_degree, tasks = build_dependency_graph(df, all_columns, weight_indices)
    
    # 执行拓扑排序
    _ = perform_topological_sort(graph, in_degree, tasks, user_formula, all_columns, weight_indices)


if __name__ == "__main__":
    main()